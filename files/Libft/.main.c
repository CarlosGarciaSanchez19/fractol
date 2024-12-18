/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   .main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 20:53:51 by carlosg2          #+#    #+#             */
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


#include <stdio.h>
#include "libft.h"

int	main(void)
{
	char	*str1;
	char	*str2;
	char	**av;
	int		*array1;
	//int		*array2;
	int		i;
	size_t	nmemb;

	str1 = ft_itoa(ft_atoi("0"));
	printf("Test ft_atoi and itoa:\n%s\n", str1);
	free(str1);
	str1 = ft_itoa(ft_atoi("-28737632"));
	printf("%s", str1);
	printf("\nTest ft_bzero and ft_strlen:\n%s\n", str1);
	ft_bzero(str1 + 2, 2);
	printf("%s\n", str1);
	printf("%zu", ft_strlen(str1));
	free(str1);
	printf("\nTest ft_calloc:\n");
	nmemb = 4;
	array1 = (int *)ft_calloc(nmemb, sizeof(int));
	i = 0;
	while (i < (int)nmemb)
		printf("%d", array1[i++]);
	free(array1);
	printf("\nTest ft_isalnum:\n");
	str1 = "0123456789AMNZamnz @![]{}??";
	i = 0;
	printf("%s\n", str1);
	while (str1[i])
		printf("%d", ft_isalnum(str1[i++]));
	printf("\nTest ft_isalpha:\n");
	i = 0;
	while (str1[i])
		printf("%d", ft_isalpha(str1[i++]));
	printf("\nTest ft_isascii:\n");
	i = 0;
	while (str1[i])
		printf("%d", ft_isascii(str1[i++]));
	// ç = -15449
	printf("\n%d", ft_isascii(-15449));
	printf("\nTest ft_isdigit:\n");
	i = 0;
	while (str1[i])
		printf("%d", ft_isdigit(str1[i++]));
	printf("\nTest ft_isprint:\n");
	i = 0;
	while (str1[i])
		printf("%d", ft_isprint(str1[i++]));
	printf("\nTest ft_memchr:\n");
	printf("%s", str1);
	if (ft_memchr(str1, 'A', 1) == NULL)
		printf("\nAsignation of memchr is NULL.\n");
	printf("%s", (char *)ft_memchr(str1, 'A', 11));
	printf("\nTest ft_memcmp:\n");
	printf("%d\n", ft_memcmp((const char *)str1, "01235", 4));
	printf("%d\n", ft_memcmp((const char *)str1, "01235", 5));
	printf("%d", ft_memcmp((const char *)str1, "0123456789AMNZamnz @![]{}??", ft_strlen(str1) + 1));
	printf("\nTest ft_memcpy and ft_strdup:\n");
	str2 = ft_strdup("0000");
	printf("%s\n", str2);
	str2 = ft_memcpy(str2, (const char *)str1, 10);
	printf("%s", str2);
	printf("\nTest ft_memmove:\n");
	printf("%s", (char *)ft_memmove(str2 + 5, (const char *)str2, 4));
	printf("\nTest ft_memset:\n");
	i = 0;
	while (i < 4)
	{
		ft_memset(str2 + i, i + '0', 1);
		i++;
	}
	printf("%s", str2);
	free(str2);
	printf("\nTest ft_split:\n");
	str1 = "   Ciao mi chiamo Carletto piaccere.   ";
	av = ft_split(str1, ' ');
	i = 0;
	while (av[i])
		printf("%s\\n\n", av[i++]);
	printf("Test ft_strchr:\n");
	str2 = ft_strchr(str1, 'c');
	printf("%s", str2);
	printf("\nTest ft_striteri:\n");
	printf("\nTest ft_strlcat:\n");
	str2 = av[0];
	i = 1;
	while (av[i])
		ft_strlcat(str2, av[i++], 100);
	printf("%s", str2);
	i = 0;
	while (av[i])
		free(av[i++]);
	free(av);
	printf("\nTest ft_strtrim and ft_substr:\n");
	str1 = "iiaedHey what's up?eiadidea";
	printf("%s\n", str1);
	str2 = ft_strtrim(str1, "adei");
	printf("%s\n", str2);
	free(str2);
}
