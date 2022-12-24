/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vegret <victor.egret.pro@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 19:47:08 by vegret            #+#    #+#             */
/*   Updated: 2022/12/24 23:38:30 by vegret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	stop_server(int sig)
{
	(void) sig;
	ft_printf("\nServer stopped by SIGINT\n");
	exit(0);
}

void	receive(int sig)
{
	static unsigned char	current_char = 0;
	static int				i = 0;

	current_char |= (sig == SIGUSR1) << i;
	i++;
	if (i == 8)
	{
		write(1, &current_char, 1);
		current_char = 0;
		i = 0;
	}
}

int	main(void)
{
	if (signal(SIGUSR1, &receive) == SIG_ERR)
		return (ft_printf("Failed SIGUSR1 handling"), 1);
	if (signal(SIGUSR2, &receive) == SIG_ERR)
		return (ft_printf("Failed SIGUSR2 handling"), 1);
	if (signal(SIGINT, &stop_server) == SIG_ERR)
		return (ft_printf("Failed SIGINT handling"), 1);
	ft_printf("Server's PID: %d\n", getpid());
	while (1)
		pause();
	return (0);
}
