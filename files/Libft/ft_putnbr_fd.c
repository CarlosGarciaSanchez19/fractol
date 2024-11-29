/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:03:42 by carlosg2          #+#    #+#             */
/*   Updated: 2024/11/26 12:54:40 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_fd(int n, int fd)
{
	char	nbr;
	int		wrtcalls;

	wrtcalls = 0;
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return (11);
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
		wrtcalls++;
	}
	if (n > 9)
		wrtcalls += ft_putnbr_fd(n / 10, fd);
	nbr = (n % 10) + '0';
	write(fd, &nbr, 1);
	return (++wrtcalls);
}
