/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 10:57:00 by carlosg2          #+#    #+#             */
/*   Updated: 2024/12/18 01:53:06 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Copyright © 2024 Carlos García Sánchez. All rights reserved.
 * Unauthorized copying, distribution, modification, or use of this software, 
 * in whole or in part, is strictly prohibited without explicit permission from the copyright owner.
 * This software is provided "as is" without any warranty, express or implied. 
 * Use is at your own risk.
 */


#include "libft.h"

static int	putarg(char c, va_list args)
{
	if (c == 'c')
		return (ft_putchar_fd(va_arg(args, int), 1));
	else if (c == 's')
		return (ft_putstr_fd(va_arg(args, char *), 1));
	else if (c == 'd' || c == 'i')
		return (ft_putnbr_fd(va_arg(args, int), 1));
	else if (c == 'u')
		return (ft_putunsnbr_fd(va_arg(args, unsigned int), 1));
	else if (c == 'x')
		return (ft_putnbr_hex_fd(va_arg(args, unsigned int), 1, 0));
	else if (c == 'X')
		return (ft_putnbr_hex_fd(va_arg(args, unsigned int), 1, 1));
	else if (c == 'p')
		return (ft_putpointer_fd(va_arg(args, uintptr_t), 1));
	else if (c == '%')
		write(1, "%", 1);
	else
		write(1, &c, 1);
	return (1);
}

int	ft_printf(char const *s, ...)
{
	va_list		args;
	int			i;
	int			count;

	if (s == NULL)
		return (ft_putstr_fd(NULL, 1));
	va_start(args, s);
	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == '%')
		{
			i++;
			count += putarg(s[i], args);
		}
		else
		{
			count++;
			write(1, &s[i], 1);
		}
		i++;
	}
	return (count);
}
