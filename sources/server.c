/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vegret <victor.egret.pro@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 19:47:08 by vegret            #+#    #+#             */
/*   Updated: 2022/12/24 01:30:37 by vegret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	stop_server(int sig)
{
	(void) sig;
	ft_printf("Server stopped by SIGINT\n");
	exit(0);
}

void	receive(int sig)
{
	static char	current_char = 0;
	static int	i = 0;

	current_char |= (sig == SIGUSR1) << i;
	i++;
	if (i == 8)
	{
		ft_printf("%c", current_char);
		current_char = 0;
		i = 0;
	}
}

int	main(void)
{
	ft_printf("Server's PID: %d\n", getpid());
	while (1)
	{
		signal(SIGUSR1, &receive);
		signal(SIGUSR2, &receive);
		signal(SIGINT, &stop_server);
	}
	return (0);
}
