/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vegret <victor.egret.pro@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 19:30:55 by vegret            #+#    #+#             */
/*   Updated: 2022/12/23 20:20:52 by vegret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	ft_isspace(int c)
{
	return (c == 32 || (c > 8 && c < 14));
}

static int	ft_atoi(const char *nptr)
{
	long	result;
	int		sign;
	int		i;

	result = 0;
	i = 0;
	while (ft_isspace(nptr[i]))
		i++;
	sign = 1;
	if (nptr[i] == '-' || nptr[i] == '+')
		if (nptr[i++] == '-')
			sign = -1;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if (result > (LONG_MAX / 10))
			return (-1 * (sign == 1));
		result = result * 10 + nptr[i++] - 48;
		if (result < 0)
			return (-1 * (sign == 1));
	}
	return (result * sign);
}

int	send_char(t_pid pid, char c)
{
	
	return (0);
}

int	send_message(t_pid pid, char *message)
{
	int	i;

	i = 0;
	while (message[i])
	{
		if (send_char(pid, message[i]))
			return (1);
		i++;
	}
	return (0);
}

int	main(int argc, char const *argv[])
{
	pid_t	pid;

	if (argc != 3)
		return (ft_printf("Usage: %s <Servers's PID> <Message>\n", argv[0]), 1);
	pid = ft_atoi(argv[1]);
	if (pid < 1 || kill(pid, 0) != 0)
		return (ft_printf("Invalid PID\n"), 1);
	return (send_message(pid, argv[2]));
}
