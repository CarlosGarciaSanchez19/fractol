/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vars_mse_zoom.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 18:35:23 by carlosg2          #+#    #+#             */
/*   Updated: 2024/12/02 16:22:55 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	init_display(t_vars *vars, char **argv)
{
	char	*title;

	title = ft_strjoin("Fractol - ", argv[1]);
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, WIDTH, HEIGHT, title);
	free(title);
	vars->img.img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	vars->img.addr = mlx_get_data_addr(vars->img.img, &vars->img.bits_per_pixel,
			&vars->img.line_length, &vars->img.endian);
}

static void	init_view(t_vars *vars)
{
	double	strt_edgs;

	strt_edgs = 3.0;
	vars->view.x_min = -strt_edgs;
	vars->view.x_max = strt_edgs;
	vars->view.y_min = -strt_edgs;
	vars->view.y_max = strt_edgs;
	vars->view.scale = 1.0;
	adjust_aspect_ratio(vars, (double)WIDTH / (double)HEIGHT);
}

void	init_vars(t_vars *vars, char **argv)
{
	init_display(vars, argv);
	init_view(vars);
	vars->max_iter = 0;
	vars->aug_iter = 0;
	vars->mse_is_down = 0;
	vars->ctrl_is_down = 0;
	if (!ft_strcmp(argv[1], "BurningShip"))
		vars->precision = 0;
	else
		vars->precision = 10;
	if (argv[2] && !argv[3])
	{
		vars->precision = ft_atoi(argv[2]);
		vars->c = (t_cmplx){-0.835, 0.2321};
	}
	else if (argv[2] && argv[3])
		vars->c = (t_cmplx){ft_atod(argv[2]), ft_atod(argv[3])};
	else
		vars->c = (t_cmplx){-0.835, 0.2321};
	vars->palette = 0;
	vars->color_freq = 1.0;
	vars->fractal = argv[1];
	color_fill(vars, rainbow_color);
}
/* Curious julia fractal with "pilars" in its vortexes:
vars->c = (t_cmplx){-0.835, 0.2321}; */

static void	apply_zoom(t_vars *vars, double f, t_cmplx mouse)
{
	t_limits	lm_x;
	t_limits	lm_y;

	lm_x.min = &vars->view.x_min;
	lm_x.max = &vars->view.x_max;
	lm_y.min = &vars->view.y_min;
	lm_y.max = &vars->view.y_max;
	if (vars->view.scale <= 0.2)
	{
		vars->view.scale = 0.2;
		return ;
	}
	*lm_x.min = mouse.a - (mouse.a - *lm_x.min) * f;
	*lm_x.max = mouse.a + (*lm_x.max - mouse.a) * f;
	*lm_y.min = mouse.b - (mouse.b - *lm_y.min) * f;
	*lm_y.max = mouse.b + (*lm_y.max - mouse.b) * f;
}

int	mouse_zoom(int button, int x, int y, t_vars *vars)
{
	double		factor;
	t_cmplx		mouse;
	t_limits	limits_x;
	t_limits	limits_y;
	double		*scale;

	factor = 1.0;
	limits_x.min = &vars->view.x_min;
	limits_x.max = &vars->view.x_max;
	limits_y.min = &vars->view.y_min;
	limits_y.max = &vars->view.y_max;
	mouse.a = from_int_to_real(x, *limits_x.min, *limits_x.max, WIDTH);
	mouse.b = from_int_to_real(y, *limits_y.min, *limits_y.max, HEIGHT);
	if (button == 4)
		factor = 0.95;
	else if (button == 5)
		factor = 1 / 0.95;
	else if (button == 1)
		return (mouse_down(mouse, vars));
	scale = &vars->view.scale;
	*scale /= factor;
	apply_zoom(vars, factor, mouse);
	return (0);
}
