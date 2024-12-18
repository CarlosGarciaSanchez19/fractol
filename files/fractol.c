/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:51:12 by carlosg2          #+#    #+#             */
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

void	print_sec(t_th_data *dt, void (*fractal)(t_vars *, t_cmplx, t_point))
{
	int		i;
	int		j;
	t_cmplx	z;
	t_point	point;

	z.a = 0;
	z.b = 0;
	i = 0;
	while (i < WIDTH)
	{
		j = dt->start_y;
		while (j < dt->end_y)
		{
			z.a = from_int_to_real(i, dt->vars->view.x_min,
					dt->vars->view.x_max, WIDTH);
			z.b = from_int_to_real(j, dt->vars->view.y_min,
					dt->vars->view.y_max, HEIGHT);
			point.x = i;
			point.y = j++;
			fractal(dt->vars, z, point);
		}
		i++;
	}
}

void	*render_section(void *arg)
{
	t_th_data	*data;

	data = (t_th_data *)arg;
	if (!ft_strcmp(data->vars->fractal, "Mandelbrot"))
		print_sec(data, mandelbrot);
	else if (!ft_strcmp(data->vars->fractal, "Julia"))
		print_sec(data, julia);
	else if (!ft_strcmp(data->vars->fractal, "BurningShip"))
		print_sec(data, burning_ship);
	return (NULL);
}

static void	put_image_and_increase_iter(t_vars *vars)
{
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	mlx_do_sync(vars->mlx);
	if (vars->aug_iter >= vars->precision * (int)log(vars->view.scale + 1.0))
		vars->aug_iter = vars->precision * (int)log(vars->view.scale + 1.0);
	else
		vars->aug_iter += vars->precision / 20
			* (int)log(vars->view.scale + 1.0);
}

int	render_next_frame(t_vars *vars)
{
	pthread_t		threads[THREADS];
	t_th_data		data[THREADS];
	int				section_height;
	int				i;

	mse_julia_adjust(vars);
	mlx_clear_window(vars->mlx, vars->win);
	section_height = HEIGHT / THREADS;
	i = 0;
	while (i < THREADS)
	{
		data[i].vars = vars;
		data[i].start_y = i * section_height;
		data[i].end_y = (i + 1) * section_height;
		pthread_create(&threads[i], NULL, render_section, &data[i]);
		i++;
	}
	i = 0;
	while (i < THREADS)
		pthread_join(threads[i++], NULL);
	put_image_and_increase_iter(vars);
	return (0);
}

int	main(int argc, char **argv)
{
	t_vars	vars;
	int		colormap[NUM_COLORS];

	if (argc >= 2 && argc <= 4)
	{
		if (!parse_input_bonus(argc, argv))
			return (0);
		vars.colormap = colormap;
		init_vars(&vars, argv);
		mlx_hook(vars.win, 17, 1L << 17, close_window, &vars);
		mlx_hook(vars.win, 2, 1L << 0, key_press, &vars);
		mlx_hook(vars.win, 3, 1L << 1, key_release, &vars);
		mlx_hook(vars.win, 5, 1L << 3, mouse_up, &vars);
		mlx_mouse_hook(vars.win, mouse_zoom, &vars);
		mlx_loop_hook(vars.mlx, render_next_frame, &vars);
		mlx_loop(vars.mlx);
	}
	else if (argc == 1 || argc > 4)
	{
		print_options(" ");
		return (0);
	}
	return (0);
}

