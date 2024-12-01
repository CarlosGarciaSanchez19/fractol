/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:42:53 by carlosg2          #+#    #+#             */
/*   Updated: 2024/12/01 18:33:18 by carlosg2         ###   ########.fr       */
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
		if (vars->view.scale <= 5.0)
		{
			vars->c.a = from_int_to_real(x, vars->view.x_min,
					vars->view.x_max, WIDTH);
			vars->c.b = from_int_to_real(y, vars->view.y_min,
					vars->view.y_max, HEIGHT);
		}
	}
	return (0);
}

int	mouse_down(t_cmplx mouse, t_vars *vars)
{
	if (vars->view.scale <= 5.0)
		vars->c = mouse;
	vars->mse_is_down = 1;
	return (0);
}

void	fractal_pxl_put(t_vars *vars, t_cmplx z, t_point point, int out_iter)
{
	int		color;
	int		color_brand_smoother;

	color_brand_smoother = (int)(log(log(z.a * z.a + z.b * z.b))
			/ log(vars->max_iter));
	if (out_iter == vars->max_iter)
		my_mlx_pixel_put(&(vars->img), point.x, point.y, 0);
	else
	{
		color = out_iter + 1 - color_brand_smoother;
		my_mlx_pixel_put(&(vars->img),
			point.x, point.y, vars->colormap[color % NUM_COLORS]);
	}
}
