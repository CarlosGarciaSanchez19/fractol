/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:01:30 by carlosg2          #+#    #+#             */
/*   Updated: 2024/09/27 17:03:33 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t		j;
	size_t		i;

	if (little[0] == '\0')
		return ((char *)big);
	i = 0;
	while (big[i])
	{
		j = 0;
		if (big[i] == little[j])
		{
			while ((big[i + j] == little[j]) && little[j] && (i + j) < len)
				j++;
			if (little[j] == '\0')
				return ((char *)(big + i));
		}
		i++;
	}
	return (NULL);
}
