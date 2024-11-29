/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:51:12 by carlosg2          #+#    #+#             */
/*   Updated: 2024/11/29 16:23:50 by carlosg2         ###   ########.fr       */
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

/* int	print_key(int keycode, t_vars *vars)
{
	printf("%d\n", keycode);
	return (0);
} */

void	print_frame(t_vars *vars, void (*fractal)(t_vars *, t_cmplx, t_point))
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
		j = 0;
		while (j < HEIGHT)
		{
			z.a = from_int_to_real(i, vars->view.x_min, vars->view.x_max, WIDTH);
			z.b = from_int_to_real(j, vars->view.y_min, vars->view.y_max, HEIGHT);
			point.x = i;
			point.y = j++;
			fractal(vars, z, point);
		}
		i++;
	}
}

void	render_frame(t_vars *vars)
{
	if (!ft_strcmp(vars->fractal, "Mandelbrot"))
		print_frame(vars, mandelbrot);
	else if (!ft_strcmp(vars->fractal, "Julia"))
		print_frame(vars, julia);
}

int	render_next_frame(t_vars *vars)
{
	int	*aug_iter;

	mse_julia_adjust(vars);
	mlx_clear_window(vars->mlx, vars->win);
	aug_iter = &vars->aug_iter;
	render_frame(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	mlx_do_sync(vars->mlx);
	printf("%d\n", *aug_iter);
	if (*aug_iter >= vars->precision * (int)log(vars->view.scale + 1.0))
		*aug_iter = vars->precision * (int)log(vars->view.scale + 1.0);
	else
		*aug_iter += vars->precision / 40 * (int)log(vars->view.scale + 1.0);
	return (0);
}

static void	print_options(char *str)
{
	ft_printf("Select a%sfractal:\n---> Mandelbrot\n", str);
	ft_printf("---> Julia\n\nWith optional parameters:\n");
	ft_printf("--> Precision = [integer]\n             ");
	ft_printf("or\n--> Julia parameter = [double] [double]\n");
}

int	parse_input(int argc, char **argv)
{
	int i;

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

int	main(int argc, char **argv)
{
	t_vars	vars;

	if (argc >= 2 && argc <= 4)
	{
		if (!parse_input(argc, argv))
			return (0);
		vars.colormap = malloc(sizeof(int) * NUM_COLORS);
		init_vars(&vars, argv);
		mlx_hook(vars.win, 17, 1L << 17, close_window, &vars);
		mlx_hook(vars.win, 5, 1L << 3, mouse_up, &vars);
		mlx_mouse_hook(vars.win, mouse_zoom, &vars);
		mlx_key_hook(vars.win, key, &vars);
		mlx_loop_hook(vars.mlx, render_next_frame, &vars);
		mlx_loop(vars.mlx);
	}
	else if (argc == 1)
	{
		print_options(" ");
		return (0);
	}
	return (free(vars.colormap), 0);
}

