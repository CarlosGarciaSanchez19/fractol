/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press_management.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 13:23:24 by carlosg2          #+#    #+#             */
/*   Updated: 2024/12/01 18:50:44 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (keycode == 101)
	{
		vars->precision += 10;
		ft_printf("Precision increased to: %d\n", vars->precision);
		ft_printf("Iterations increased in: %d\n", vars->aug_iter);
	}
	else if (keycode == 113)
	{
		if (vars->precision >= 10)
		{
			vars->precision -= 10;
			ft_printf("Precision decreased to: %d\n", vars->precision);
			ft_printf("Iterations decreased in: %d\n", vars->aug_iter);
		}
		else
			ft_printf("Precision not decreased, it stays at: %d\n",
				vars->precision);
	}
}

static void	home_and_color_freq_manag(int keycode, t_vars *vars)
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
	else if (keycode == 45)
		vars->color_freq /= 1.5;
	else if (keycode == 43)
	{
		vars->color_freq *= 1.5;
		if (vars->color_freq > 10.0)
			vars->color_freq = 10.0;
	}
}

static void	colormap_type_manag(int keycode, t_vars *vars)
{
	if (keycode == 99)
	{
		vars->colormap_type++;
		if (vars->colormap_type > 7)
			vars->colormap_type = 0;
	}
	if (vars->colormap_type == RAINBOW)
		color_fill(vars, rainbow_color);
	else if (vars->colormap_type == WHITE_TO_SIENA)
		color_fill(vars, white_to_color);
	else if (vars->colormap_type == WHITE_TO_RED)
		color_fill(vars, white_to_color);
	else if (vars->colormap_type == WHITE_TO_BLUE)
		color_fill(vars, white_to_color);
	else if (vars->colormap_type == WHITE_TO_GREEN)
		color_fill(vars, white_to_color);
	else if (vars->colormap_type == RED_TO_YELLOW)
		color_fill(vars, red_to_yellow);
	else if (vars->colormap_type == BLUE_TO_GOLD)
		color_fill(vars, blue_to_gold);
	else if (vars->colormap_type == BLUE_TO_GOLD_TO_RED)
		color_fill(vars, blue_to_gold_to_red);
}

int	key_press(int keycode, t_vars *vars)
{
	if (keycode == 65507)
		vars->ctrl_is_down = 1;
	awsd_management(keycode, vars);
	precision_management(keycode, vars);
	home_and_color_freq_manag(keycode, vars);
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
	colormap_type_manag(keycode, vars);
	return (0);
}
