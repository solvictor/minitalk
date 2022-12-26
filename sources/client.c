/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vegret <victor.egret.pro@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 19:30:55 by vegret            #+#    #+#             */
/*   Updated: 2022/12/26 17:03:54 by vegret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	g_response = 0;

static int	parse_pid(const char *s)
{
	long	pid;
	int		i;

	pid = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (-1);
		pid = pid * 10 + s[i] - '0';
		i++;
	}
	return (pid);
}

static int	send_char(int pid, unsigned char c)
{
	int	i;
	int	res;

	i = 0;
	while (i < 8)
	{
		if (c % 2)
			res = kill(pid, SIGUSR1);
		else
			res = kill(pid, SIGUSR2);
		if (res == -1)
			return (1);
		c >>= 1;
		i++;
		while (!g_response)
			pause();
		g_response = 0;
	}
	return (0);
}

static int	send_message(int pid, char *message)
{
	if (!*message)
		return (0);
	while (*message)
	{
		if (send_char(pid, (unsigned char) *message))
			return (ft_printf("Failed to send a character\n"), 1);
		message++;
	}
	if (send_char(pid, (unsigned char) 0))
		return (ft_printf("Failed to send message end\n"), 1);
	ft_printf("Server successfully received message\n");
	return (0);
}

static void	receive(int sig)
{
	if (sig == SIGUSR1)
		g_response = 1;
}

int	main(int argc, char *argv[])
{
	int					pid;
	struct sigaction	action;

	if (argc != 3)
		return (ft_printf("Usage: %s <Servers's PID> <Message>\n", argv[0]), 1);
	pid = parse_pid(argv[1]);
	if (pid < 1 || kill(pid, 0) == -1)
		return (ft_printf("Invalid PID\n"), 1);
	action.sa_handler = &receive;
	action.sa_flags = SA_RESTART;
	if (sigemptyset(&action.sa_mask) != 0)
		return (ft_printf("Failed action initialization\n"), 1);
	if (sigaction(SIGUSR1, &action, NULL) == -1)
		return (ft_printf("Failed SIGUSR1 handling\n"), 1);
	return (send_message(pid, argv[2]));
}
