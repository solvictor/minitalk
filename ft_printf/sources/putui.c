/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putui.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vegret <victor.egret.pro@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 19:17:44 by vegret            #+#    #+#             */
/*   Updated: 2022/11/15 10:47:20 by vegret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	uintlen(unsigned int n)
{
	int	len;

	len = 1;
	while (n > 9)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static int	putui_aux(unsigned int n)
{
	if (n < 10)
		return (putchar_c(n + '0', NULL));
	return (putui_aux(n / 10) + putui_aux(n % 10));
}

static int	printinglen(unsigned int n, t_flag *flag)
{
	int	len;

	len = uintlen(n);
	if (flag && flag->flags & DOT && flag->precision > len)
		len = flag->precision;
	if (n == 0 && flag && flag->flags & DOT && flag->precision == 0)
		len = 0;
	return (len);
}

int	putui(unsigned int n, t_flag *flag)
{
	int	printed;

	printed = 0;
	if (!(flag && flag->flags & ZERO))
		printed = fill_before(flag, printinglen(n, flag));
	printed += putzeros(flag, uintlen(n), 0);
	if (n == 0 && flag && flag->flags & DOT && flag->precision == 0)
		return (printed);
	if (n < 10)
		printed += putui_aux(n);
	else
		printed += putui_aux(n / 10) + putui_aux(n % 10);
	return (printed);
}
