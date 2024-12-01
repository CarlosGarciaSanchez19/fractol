/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input_print_opt.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 22:57:15 by carlosg           #+#    #+#             */
/*   Updated: 2024/12/01 18:41:39 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	print_options(char *str)
{
	ft_printf("Select a%sfractal:\n---> Mandelbrot\n", str);
	ft_printf("---> Julia\n\nWith optional parameters:\n");
	ft_printf("--> Precision = [integer]\n             ");
	ft_printf("or\n--> Julia parameter = [double] [double]\n");
}

int	parse_input(int argc, char **argv)
{
	int	i;

	i = 2;
	while (argv[i])
	{
		if (!ft_strisnumber(argv[i]))
		{
			if (argc == 3)
				ft_printf("\nInvalid precision.\n\n");
			if (argc == 4)
				ft_printf("\nInvalid Julia parameter.\n\n");
			print_options(" ");
			return (0);
		}
		i++;
	}
	if (!ft_strcmp(argv[1], "Mandelbrot") || !ft_strcmp(argv[1], "Julia"))
		return (1);
	else
		print_options(" valid ");
	return (0);
}

void	print_options_bonus(char *str)
{
	ft_printf("Select a%sfractal:\n---> Mandelbrot\n", str);
	ft_printf("---> Julia\n---> BurningShip\n\nWith optional parameters:\n");
	ft_printf("--> Precision = [integer]\n             ");
	ft_printf("or\n--> Julia parameter = [double] [double]\n");
}

int	parse_input_bonus(int argc, char **argv)
{
	int	i;

	i = 2;
	while (argv[i])
	{
		if (!ft_strisnumber(argv[i]))
		{
			if (argc == 3)
				ft_printf("\nInvalid precision.\n\n");
			if (argc == 4)
				ft_printf("\nInvalid Julia parameter.\n\n");
			print_options_bonus(" ");
			return (0);
		}
		i++;
	}
	if (!ft_strcmp(argv[1], "Mandelbrot") || !ft_strcmp(argv[1], "Julia")
		|| !ft_strcmp(argv[1], "BurningShip"))
		return (1);
	else
		print_options_bonus(" valid ");
	return (0);
}
