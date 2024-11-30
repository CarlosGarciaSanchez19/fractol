/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:51:12 by carlosg2          #+#    #+#             */
/*   Updated: 2024/11/30 22:37:41 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	t_th_data 	*data = (t_th_data *)arg;
	
	
	if (!ft_strcmp(data->vars->fractal, "Mandelbrot"))
		print_sec(data, mandelbrot);
	else if (!ft_strcmp(data->vars->fractal, "Julia"))
		print_sec(data, julia);
	else if (!ft_strcmp(data->vars->fractal, "BurningShip"))
		print_sec(data, burning_ship);
	return (NULL);
}

int	render_next_frame(t_vars *vars)
{
	pthread_t		threads[THREADS];
	t_th_data		data[THREADS];
	int				section_height;
	int				i;
	int				*aug_iter;

	mse_julia_adjust(vars);
	mlx_clear_window(vars->mlx, vars->win);
	section_height = HEIGHT / THREADS;
	aug_iter = &vars->aug_iter;
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
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	mlx_do_sync(vars->mlx);
	/* printf("%d\n", *aug_iter); */
	if (*aug_iter >= vars->precision * (int)log(vars->view.scale + 1.0))
		*aug_iter = vars->precision * (int)log(vars->view.scale + 1.0);
	else
		*aug_iter += vars->precision / 40 * (int)log(vars->view.scale + 1.0);
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
	int i;

	i = 2;
	while (argv[i])
	{
		if (!ft_strisnumber(argv[i]))
		{
			if (argc == 3)
				printf("\nInvalid precision.\n\n");
			if (argc == 4)
				printf("\nInvalid Julia parameter.\n\n");
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

int	main(int argc, char **argv)
{
	t_vars	vars;

	if (argc >= 2 && argc <= 4)
	{
		if (!parse_input_bonus(argc, argv))
			return (0);
		vars.colormap = malloc(sizeof(int) * NUM_COLORS);
		init_vars(&vars, argv);
		mlx_hook(vars.win, 17, 1L << 17, close_window, &vars);
		//mlx_hook(vars.win, 4, 1L << 2, mouse_down, &vars);
		mlx_hook(vars.win, 5, 1L << 3, mouse_up, &vars);
		mlx_mouse_hook(vars.win, mouse_zoom, &vars);
		mlx_key_hook(vars.win, key, &vars);
		mlx_loop_hook(vars.mlx, render_next_frame, &vars);
		mlx_loop(vars.mlx);
	}
	else if (argc == 1)
	{
		print_options_bonus(" ");
		return (0);
	}
	return (free(vars.colormap), 0);
}

