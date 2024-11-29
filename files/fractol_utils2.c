/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:42:53 by carlosg2          #+#    #+#             */
/*   Updated: 2024/11/29 16:13:03 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	adjust_aspect_ratio(t_vars *vars, double asp_ratio)
{
	t_cmplx	center;
	t_cmplx	range;


	center.a = (vars->view.x_max + vars->view.x_min) / 2;
	center.b = (vars->view.y_max + vars->view.y_min) / 2;
	range.a = vars->view.x_max - vars->view.x_min;
	range.b = vars->view.y_max - vars->view.y_min;
	if (asp_ratio > 1.0)
	{
		vars->view.x_min = center.a - range.a * asp_ratio / 2;
		vars->view.x_max = center.a + range.a * asp_ratio / 2;
	}
	else
	{
		vars->view.y_min = center.b - range.b * asp_ratio / 2;
		vars->view.y_max = center.b + range.b * asp_ratio / 2;
	}
}

int	mouse_up(int button, int x, int y, t_vars *vars)
{
	if (button == 1)
	{
		vars->mse_is_down = 0;
		vars->c.a = from_int_to_real(x, vars->view.x_min, vars->view.x_max, WIDTH);
		vars->c.b = from_int_to_real(y, vars->view.y_min, vars->view.y_max, HEIGHT);
	}
	return (0);
}

int	mouse_down(t_cmplx mouse, t_vars *vars)
{
	vars->c = mouse;
	vars->mse_is_down = 1;
	return (0);
}

void	mse_julia_adjust(t_vars *vars)
{
	int	mse_x;
	int	mse_y;

	mlx_mouse_get_pos(vars->mlx, vars->win, &mse_x, &mse_y);
	if (vars->mse_is_down)
	{
		vars->c.a = from_int_to_real(mse_x, vars->view.x_min, vars->view.x_max, WIDTH);
		vars->c.b = from_int_to_real(mse_y, vars->view.y_min, vars->view.y_max, HEIGHT);
	}
}

void	fractal_pixel_put(t_vars *vars, t_cmplx z, t_point point, int out_iter)
{
	int		color;

	/* (void)z; */
	if (out_iter == vars->max_iter)
		my_mlx_pixel_put(&(vars->img), point.x, point.y, 0);
	else
	{
		/* color = (int)((complex_mod(z) - 2.0) * 255.0 / 2.0); */
		color = out_iter + 1 - (int)(log(log(z.a * z.a + z.b * z.b)) / log((double)vars->max_iter));
		my_mlx_pixel_put(&(vars->img), point.x, point.y, vars->colormap[color % NUM_COLORS]);
	}
}
/* Curious julia fractal with "pilars" in its vortexes:
vars->c = (t_cmplx){-0.835, 0.2321}; */
