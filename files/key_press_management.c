/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press_management.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 13:23:24 by carlosg2          #+#    #+#             */
/*   Updated: 2024/12/05 10:54:21 by carlosg2         ###   ########.fr       */
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
		ft_printf("Maximum iterations are now: %d\n", vars->precision
			* (int)log(vars->view.scale + 1));
	}
	else if (keycode == 113)
	{
		if (vars->precision >= 10)
		{
			vars->precision -= 10;
			ft_printf("Precision decreased to: %d\n", vars->precision);
			ft_printf("Maximum iterations are now: %d\n", vars->precision
				* (int)log(vars->view.scale + 1));
		}
		else
		{
			ft_printf("Precision not decreased, it stays at: %d\n",
				vars->precision);
			ft_printf("Maximum iterations stay at: %d\n", vars->precision
				* (int)log(vars->view.scale + 1));
		}
	}
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
