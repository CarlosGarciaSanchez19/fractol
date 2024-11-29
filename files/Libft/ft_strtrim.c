/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:33:46 by carlosg2          #+#    #+#             */
/*   Updated: 2024/09/25 01:39:32 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		first;
	int		last;
	char	*strtrimmed;

	first = 0;
	last = ft_strlen(s1) - 1;
	if (s1 == NULL || set == NULL)
		return (NULL);
	while (s1[first] && ft_strchr(set, s1[first]))
		first++;
	while (last >= 0 && ft_strchr(set, s1[last]))
		last--;
	strtrimmed = ft_substr(s1, first, last - first + 1);
	return (strtrimmed);
}
