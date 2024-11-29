/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:51:12 by carlosg2          #+#    #+#             */
/*   Updated: 2024/11/29 16:24:44 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/* void	put_circle(t_data *img, t_vars *vars, int color)
{
	this function puts a circle supposing the image has the same size as the window
	double i;

	if (vars->r < 0)
		vars->r = 0;
	i = 0;
	while(i < 2 * M_PI)
	{
		my_mlx_pixel_put(img, vars->x + vars->r * cos(i), vars->y + vars->r * sin(i), color);
		i += 0.0001;
	}
} */

/* void	put_gradient(t_data *img, int x, int y, int color)
{
	int i;
	int width;
	int j;

	width = 200;
	i = 0;
	while(i < width)
	{
		j = 0;
		while (j < width)
		{
			my_mlx_pixel_put(img, x - width / 2 + i, y - width / 2 + j, color);
			j++;
		}
		i++;
	}
} */

/* int	print_key(int keycode, t_vars *vars)
{
	printf("%d\n", keycode);
	return (0);
} */

void	print_section(t_thread_data *data, void (*fractal)(t_vars *, t_cmplx, t_point))
{
	int i;
	int j;
	t_cmplx z;
	t_point point;

	z.a = 0;
	z.b = 0;
	i = 0;
	while (i < WIDTH)
	{
		j = data->start_y;
		while (j < data->end_y)
		{
			z.a = from_int_to_real(i, data->vars->view.x_min, data->vars->view.x_max, WIDTH);
			z.b = from_int_to_real(j, data->vars->view.y_min, data->vars->view.y_max, HEIGHT);
			point.x = i;
			point.y = j++;
			fractal(data->vars, z, point);
		}
		i++;
	}
}

void	*render_section(void *arg)
{
	t_thread_data 	*data = (t_thread_data *)arg;
	
	if (!ft_strcmp(data->vars->fractal, "Mandelbrot"))
		print_section(data, mandelbrot);
	else if (!ft_strcmp(data->vars->fractal, "Julia"))
		print_section(data, julia);
	else if (!ft_strcmp(data->vars->fractal, "BurningShip"))
		print_section(data, burning_ship);
	else if (!ft_strcmp(data->vars->fractal, "JuliaCosh"))
		print_section(data, julia_cosh);
	return (NULL);
}

int	render_next_frame(t_vars *vars)
{
	pthread_t		threads[THREADS];
	t_thread_data	data[THREADS];
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

