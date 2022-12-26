/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vegret <victor.egret.pro@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 19:47:08 by vegret            #+#    #+#             */
/*   Updated: 2022/12/26 02:16:15 by vegret           ###   ########.fr       */
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

static int	add_uc(t_uclist **message, unsigned char data)
{
	t_uclist	*new;
	t_uclist	*tmp;

	new = malloc(sizeof(t_uclist));
	if (!new)
		return (1);
	new->data = data;
	new->next = NULL;
	if (!*message)
	{
		*message = new;
		return (0);
	}
	tmp = *message;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (0);
}

static void	receive(int sig, siginfo_t *info, void *context)
{
	static t_uclist			*current_message;
	static unsigned char	current_char = 0;
	static int				i = 0;

	(void) context;
	current_char |= (sig == SIGUSR1) << i;
	i++;
	if (i == 8)
	{
		if (current_char == 0)
		{
			print_message(current_message);
			clear_message(&current_message);
			if (!info || kill(info->si_pid, SIGUSR1) == -1)
				ft_printf(
					"Failed to send acknowledgement to client %d\n",
					info->si_pid);
		}
		else
			if (add_uc(&current_message, current_char))
				(ft_printf("malloc() has failed\n"),
					clear_message(&current_message), exit(1));
		current_char = 0;
		i = 0;
	}
}

int	main(void)
{
	struct sigaction	action;

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
