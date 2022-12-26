/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vegret <victor.egret.pro@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 19:30:55 by vegret            #+#    #+#             */
/*   Updated: 2022/12/26 02:15:42 by vegret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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

static int	send_char(pid_t pid, unsigned char c)
{
	int	i;
	int	response;

	i = 0;
	while (i < 8)
	{
		if (c % 2)
			response = kill(pid, SIGUSR1);
		else
			response = kill(pid, SIGUSR2);
		if (response == -1)
			return (1);
		c >>= 1;
		i++;
		usleep(50);
	}
	return (0);
}

static int	send_message(pid_t pid, char *message)
{
	while (*message)
	{
		if (send_char(pid, (unsigned char) *message))
			return (ft_printf("Failed to send a character\n"), 1);
		message++;
		usleep(10);
	}
	if (send_char(pid, (unsigned char) 0))
		return (ft_printf("Failed to send message end\n"), 1);
	return (0);
}

static void	receive(int sig)
{
	(void) sig;
	ft_printf("Server successfully received message\n");
}

int	main(int argc, char *argv[])
{
	pid_t				pid;
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
