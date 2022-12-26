/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vegret <victor.egret.pro@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 19:47:08 by vegret            #+#    #+#             */
/*   Updated: 2022/12/26 16:09:13 by vegret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	print_message(t_uclist *message)
{
	while (message)
	{
		write(1, &message->data, 1);
		message = message->next;
	}
}

static void	clear_message(t_uclist **message)
{
	t_uclist	*tmp;

	while (*message)
	{
		tmp = (*message)->next;
		free(*message);
		*message = tmp;
	}
	*message = NULL;
}

static void	add_uc(t_uclist **message, unsigned char data)
{
	t_uclist	*new;
	t_uclist	*tmp;

	new = malloc(sizeof(t_uclist));
	if (!new)
		(ft_printf("malloc() has failed\n"), clear_message(message), exit(1));
	new->data = data;
	new->next = NULL;
	if (!*message)
	{
		*message = new;
		return ;
	}
	tmp = *message;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

static void	receive(int sig, siginfo_t *info, void *context)
{
	static t_uclist			*current_message;
	static unsigned char	current_char = 0;
	static int				i = 0;

	(void) context;
	current_char |= (sig == SIGUSR1) << i;
	if (++i == 8)
	{
		if (current_char == 0)
		{
			print_message(current_message);
			clear_message(&current_message);
		}
		else
			add_uc(&current_message, current_char);
		current_char = 0;
		i = 0;
	}
	if (!info || kill(info->si_pid, SIGUSR1) == -1)
		ft_printf("Failed to send acknowledgement to client %d\n",
			info->si_pid);
}

int	main(int argc, char const *argv[])
{
	struct sigaction	action;

	if (argc != 1)
		return (ft_printf("Usage: %s\n", argv[0]), 1);
	action.sa_sigaction = &receive;
	action.sa_flags = SA_SIGINFO;
	if (sigemptyset(&action.sa_mask) != 0)
		return (ft_printf("Failed action initialization\n"), 1);
	if (sigaction(SIGUSR1, &action, NULL) == -1)
		return (ft_printf("Failed SIGUSR1 handling\n"), 1);
	if (sigaction(SIGUSR2, &action, NULL) == -1)
		return (ft_printf("Failed SIGUSR2 handling\n"), 1);
	ft_printf("Server's PID: %d\n", getpid());
	while (1)
		pause();
	return (0);
}
