/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vegret <victor.egret.pro@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 19:25:37 by vegret            #+#    #+#             */
/*   Updated: 2022/12/26 01:34:07 by vegret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include	<unistd.h>
# include	<signal.h>
# include	"ft_printf.h"

typedef struct s_uclist {
	unsigned char	data;
	struct s_uclist	*next;
}				t_uclist;

#endif