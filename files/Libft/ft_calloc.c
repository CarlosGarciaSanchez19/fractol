/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:56:31 by carlosg2          #+#    #+#             */
/*   Updated: 2024/11/03 12:29:59 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*ptr;

	if (nmemb != 0 && size > (size_t)(-1) / nmemb)
		return (NULL);
	ptr = (char *)malloc(nmemb * size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}

/* #include <stdio.h>

int	main(int ac, char **av)
{
	char **s[2];

	if (ac == 3)
	{
			s[0] = ft_calloc(ft_atoi(av[1]), ft_atoi(av[2]));
			s[1] = calloc(ft_atoi(av[1]), ft_atoi(av[2]));
		if (s[0][0] == s[1][0])
			printf("%s\n", "SUCCESS");
		else
			printf("%s\n", "FAIL");
	}
	else if (ac == 1)
	{
		s[0] = ft_calloc(87129847891273939, 1);
		s[1] = calloc(2147483648, 1);
		if (s[0][0] == s[1][0])
			printf("%s\n", "SUCCESS");
		else
			printf("%s\n", "FAIL");
		free(s[0]);
		free(s[1]);
	}
} */
