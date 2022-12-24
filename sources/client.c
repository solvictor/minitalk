/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vegret <victor.egret.pro@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 19:30:55 by vegret            #+#    #+#             */
/*   Updated: 2022/12/24 01:32:31 by vegret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	ft_atoi(const char *s)
{
	long	result;
	int		sign;
	int		i;

	result = 0;
	i = 0;
	while (s[i] == 32 || (s[i] > 8 && s[i] < 14))
		i++;
	sign = 1;
	if (s[i] == '-' || s[i] == '+')
		if (s[i++] == '-')
			sign = -1;
	while (s[i] >= '0' && s[i] <= '9')
	{
		if (result > (LONG_MAX / 10))
			return (-1 * (sign == 1));
		result = result * 10 + s[i++] - 48;
		if (result < 0)
			return (-1 * (sign == 1));
	}
	return (result * sign);
}

int	send_char(pid_t pid, char c)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (c & (1 << i))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		i++;
		usleep(10);
	}
	return (0);
}

int	send_message(pid_t pid, char *message)
{
	while (*message)
	{
		if (send_char(pid, *message))
			return (1);
		message++;
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	pid_t	pid;

	if (argc != 3)
		return (ft_printf("Usage: %s <Servers's PID> <Message>\n", argv[0]), 1);
	pid = ft_atoi(argv[1]);
	if (pid < 1 || kill(pid, 0) != 0)
		return (ft_printf("Invalid PID\n"), 1);
	return (send_message(pid, argv[2]));
}
