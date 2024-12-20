/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press_management.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 13:23:24 by carlosg2          #+#    #+#             */
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


#include "fractol.h"

void	awsd_management(int keycode, t_vars *vars)
{
	double	factor;

	factor = 0.075 / vars->view.scale;
	if (keycode == 119)
	{
		vars->view.y_max -= factor;
		vars->view.y_min -= factor;
	}
	else if (keycode == 115)
	{
		vars->view.y_max += factor;
		vars->view.y_min += factor;
	}
	else if (keycode == 97)
	{
		vars->view.x_max -= factor;
		vars->view.x_min -= factor;
	}
	else if (keycode == 100)
	{
		vars->view.x_max += factor;
		vars->view.x_min += factor;
	}
}

static void	precision_management(int keycode, t_vars *vars)
{
	int	max_iter;

	if (!ft_strcmp(vars->fractal, "BurningShip"))
		max_iter = 40 + (int)(log(vars->view.scale + 1.0) * 8.0);
	else
		max_iter = 65 + (int)(log(vars->view.scale + 1.0) * 8.0);
	if (keycode == 101)
	{
		vars->precision += 10;
		max_iter += vars->precision * (int)log(vars->view.scale + 1);
		ft_printf("Precision increased to: %d\n", vars->precision);
		ft_printf("Maximum iterations are now: %d\n", max_iter);
	}
	else if (keycode == 113 && vars->precision >= 10)
	{
		vars->precision -= 10;
		max_iter += vars->precision * (int)log(vars->view.scale + 1);
		ft_printf("Precision decreased to: %d\n", vars->precision);
		ft_printf("Maximum iterations are now: %d\n", max_iter);
	}
	else if (keycode == 113)
		print_maximum_iter_null_precision(vars);
}

static void	home(int keycode, t_vars *vars)
{
	if (keycode == 104)
	{
		vars->view.x_min = -2.0;
		vars->view.x_max = 2.0;
		vars->view.y_min = -2.0;
		vars->view.y_max = 2.0;
		vars->view.scale = 1.0;
		adjust_aspect_ratio(vars, (double)WIDTH / (double)HEIGHT);
	}
}

static void	palette_and_color_freq_manag(int keycode, t_vars *vars)
{
	if (keycode == 99)
	{
		vars->palette++;
		if (vars->palette > 7)
			vars->palette = 0;
	}
	else if (keycode == 45)
		vars->color_freq /= 1.5;
	else if (keycode == 43)
	{
		vars->color_freq *= 1.5;
		if (vars->color_freq > 10.0)
			vars->color_freq = 10.0;
	}
	if (vars->palette == RAINBOW)
		color_fill(vars, rainbow_color);
	else if (vars->palette == WHITE_TO_SIENA || vars->palette == WHITE_TO_RED
		|| vars->palette == WHITE_TO_GREEN || vars->palette == WHITE_TO_BLUE)
		color_fill(vars, white_to_color);
	else if (vars->palette == RED_TO_YELLOW)
		color_fill(vars, red_to_yellow);
	else if (vars->palette == BLUE_TO_GOLD)
		color_fill(vars, blue_to_gold);
	else if (vars->palette == BLUE_TO_GOLD_TO_RED)
		color_fill(vars, blue_to_gold_to_red);
}

int	key_press(int keycode, t_vars *vars)
{
	if (keycode == 65507)
		vars->ctrl_is_down = 1;
	awsd_management(keycode, vars);
	precision_management(keycode, vars);
	home(keycode, vars);
	if (keycode == 103)
		save_image_as_bmp(vars, "fractol.bmp");
	else if (keycode - 49 == MANDELBROT)
		vars->fractal = "Mandelbrot";
	else if (keycode - 49 == JULIA)
		vars->fractal = "Julia";
	else if (keycode - 49 == BURNING_SHIP)
		vars->fractal = "BurningShip";
	else if (keycode == 65307)
		close_window(vars);
	palette_and_color_freq_manag(keycode, vars);
	return (0);
}
