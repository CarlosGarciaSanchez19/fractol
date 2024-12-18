/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 16:57:48 by carlosg2          #+#    #+#             */
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

static int	count_words(char const *str, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*str)
	{
		if (*str == c)
			in_word = 0;
		else if (in_word == 0)
		{
			count++;
			in_word = 1;
		}
		str++;
	}
	return (count);
}

static int	ft_modstrlen(char const *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

static char	*create_string(char const *str, char c)
{
	char	*string;
	int		i;

	string = malloc(ft_modstrlen(str, c) + 1);
	if (!string)
		return (NULL);
	i = 0;
	while (*str && *str != c)
	{
		string[i++] = *str;
		str++;
	}
	string[i] = '\0';
	return (string);
}

void	free_array(char **array, int arr_elements)
{
	arr_elements--;
	while (arr_elements >= 0)
	{
		free(array[arr_elements]);
		array[arr_elements] = NULL;
		arr_elements--;
	}
	free(array);
	array = NULL;
}

char	**ft_split(char const *str, char c)
{
	char	**array;
	int		arr_idx;
	char	*string;

	arr_idx = 0;
	array = (char **)malloc((count_words(str, c) + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	while (*str)
	{
		if (*str == c)
			str++;
		else
		{
			string = create_string(str, c);
			if (!string)
				return (free_array(array, arr_idx), NULL);
			array[arr_idx] = string;
			arr_idx++;
			str += ft_modstrlen(str, c);
		}
	}
	array[arr_idx] = NULL;
	return (array);
}

/* 
#include <stdio.h>

int main(int ac, char **av)
{
	char	**array;
	int		i;

	if (ac == 3)
	{
		array = ft_split(av[1], av[2][0]);
		if (!array)
			return (1);
		i = 0;
		while (array[i])
		{
			printf("%s\n", array[i]);
			i++;
		}
		free_array(array, i);
	}
	return (0);
} */
