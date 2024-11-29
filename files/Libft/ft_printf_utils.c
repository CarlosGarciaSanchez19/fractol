/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:59:06 by carlosg2          #+#    #+#             */
/*   Updated: 2024/11/26 12:54:40 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putunsnbr_fd(unsigned int n, int fd)
{
	char	nbr;
	int		count;

	count = 0;
	if (n > 9)
		count += ft_putunsnbr_fd(n / 10, fd);
	nbr = (n % 10) + '0';
	write(fd, &nbr, 1);
	return (++count);
}

int	ft_putnbr_hex_fd(uintptr_t n, int fd, unsigned int capital)
{
	char			*hex_digits;
	int				wrtcalls;

	wrtcalls = 0;
	if (capital)
		hex_digits = "0123456789ABCDEF";
	else
		hex_digits = "0123456789abcdef";
	if (n > 15)
		wrtcalls += ft_putnbr_hex_fd(n / 16, fd, capital);
	write(fd, &hex_digits[n % 16], 1);
	return (++wrtcalls);
}

int	ft_putpointer_fd(uintptr_t p, int fd)
{
	if (!p)
	{
		write(fd, "(nil)", 5);
		return (5);
	}
	write(fd, "0x", 2);
	return (ft_putnbr_hex_fd(p, fd, 0) + 2);
}
