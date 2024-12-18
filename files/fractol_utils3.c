/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 18:28:05 by carlosg2          #+#    #+#             */
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

void	print_maximum_iter_null_precision(t_vars *vars)
{
	vars->precision = 0;
	ft_printf("Precision not decreased, it stays at: %d\n",
		vars->precision);
	if (!ft_strcmp(vars->fractal, "BurningShip"))
		ft_printf("Maximum iterations stay at: %d\n", 40
			+ (int)(log(vars->view.scale + 1.0) * 8.0));
	else
		ft_printf("Maximum iterations stay at: %d\n", 65
			+ (int)(log(vars->view.scale + 1.0) * 8.0));
}

int	key_release(int keycode, t_vars *vars)
{
	if (keycode == 65507)
		vars->ctrl_is_down = 0;
	return (0);
}

static void	move_image(t_vars *vars, int mse_x, int mse_y)
{
	double	mv_factor;

	mv_factor = 0.25 / vars->view.scale;
	if (mse_x < WIDTH / 2)
	{
		vars->view.x_min -= mv_factor;
		vars->view.x_max -= mv_factor;
	}
	else if (mse_x > WIDTH / 2)
	{
		vars->view.x_min += mv_factor;
		vars->view.x_max += mv_factor;
	}
	if (mse_y < HEIGHT / 2)
	{
		vars->view.y_min -= mv_factor;
		vars->view.y_max -= mv_factor;
	}
	else if (mse_y > HEIGHT / 2)
	{
		vars->view.y_min += mv_factor;
		vars->view.y_max += mv_factor;
	}
}

void	mse_julia_adjust(t_vars *vars)
{
	int		mse_x;
	int		mse_y;
	t_cmplx	mouse;

	mlx_mouse_get_pos(vars->mlx, vars->win, &mse_x, &mse_y);
	mouse.a = from_int_to_real(mse_x, vars->view.x_min,
			vars->view.x_max, WIDTH);
	mouse.b = from_int_to_real(mse_y, vars->view.y_min,
			vars->view.y_max, HEIGHT);
	if (vars->mse_is_down
		&& !(vars->view.scale > 5.0 && !ft_strcmp(vars->fractal, "Julia")))
		vars->c = mouse;
	if (vars->ctrl_is_down)
		move_image(vars, mse_x, mse_y);
}
