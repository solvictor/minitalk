/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vegret <victor.egret.pro@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 19:47:08 by vegret            #+#    #+#             */
/*   Updated: 2022/12/25 01:46:00 by vegret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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
	ft_printf("Server's PID: %d\n", getpid());
	while (1)
		pause();
	return (0);
}
