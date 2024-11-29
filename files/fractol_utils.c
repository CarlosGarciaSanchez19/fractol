/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:25:03 by carlosg2          #+#    #+#             */
/*   Updated: 2024/11/29 16:45:49 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

double	from_int_to_real(int i, double min, double max, int size)
{
	return ((double)i / (double)size * (max - min) + min);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	close_window(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->img.img);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free(vars->colormap);
	free(vars->mlx);
	exit(0);
	return (0);
}

int	key(int keycode, t_vars *vars)
{
	double	factor;

	factor = 0.15 / vars->view.scale;
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
	else if (keycode == 101)
	{
		vars->precision += 25;
		ft_printf("Precision increased to: %d\n", vars->precision);
		ft_printf("Iterations increased in: %d\n", vars->aug_iter);
	}
	else if (keycode == 113)
	{
		if (vars->precision >= 25)
		{
			vars->precision -= 25;
			ft_printf("Precision decreased to: %d\n", vars->precision);
			ft_printf("Iterations decreased in: %d\n", vars->aug_iter);
		}
		else
			ft_printf("Precision not decreased, it stays at: %d\n",
				vars->precision);
	}
	else if (keycode == 104)
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
	else if (keycode == 99)
	{
		vars->colormap_type++;
		if (vars->colormap_type > 7)
			vars->colormap_type = 0;
	}
	/* else if (keycode == 65507)
		vars->ctrl_is_down = 1; */
	else if (keycode == 103)
		save_image_as_bmp(vars, "fractol.bmp");
	else if (keycode == 49)
		vars->fractal = "Mandelbrot";
	else if (keycode == 50)
		vars->fractal = "Julia";
	else if (keycode == 51)
		vars->fractal = "BurningShip";
	else if (keycode == 65307)
		close_window(vars);
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
	/* render_next_frame(vars); */
	return (0);
}
