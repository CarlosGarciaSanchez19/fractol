/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 20:13:36 by carlosg2          #+#    #+#             */
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

static int	ft_countdigits(int n)
{
	int	ncopy;
	int	count;

	if (n == 0)
		return (1);
	ncopy = n;
	count = 0;
	while (ncopy)
	{
		ncopy /= 10;
		count++;
	}
	return (count);
}

static char	*ft_auxitoa(int i, int n)
{
	char	*strnbr;

	if (n < 0)
	{
		strnbr = malloc(i + 2);
		if (strnbr == NULL)
			return (NULL);
	}
	else
	{
		strnbr = malloc(i + 1);
		if (strnbr == NULL)
			return (NULL);
	}
	return (strnbr);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*strnbr;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	i = ft_countdigits(n);
	strnbr = ft_auxitoa(i, n);
	if (strnbr == NULL)
		return (NULL);
	if (n < 0)
	{
		strnbr[0] = '-';
		n = -n;
		i++;
	}
	strnbr[i] = '\0';
	if (n == 0)
		strnbr[0] = '0';
	while (n)
	{
		strnbr[--i] = n % 10 + '0';
		n /= 10;
	}
	return (strnbr);
}
