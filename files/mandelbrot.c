/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 13:46:30 by carlosg2          #+#    #+#             */
/*   Updated: 2024/12/04 16:01:04 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	mandelbrot(t_vars *vars, t_cmplx c, t_point point)
{
	int		i;
	t_cmplx	z;

	z = (t_cmplx){0, 0};
	i = 0;
	vars->max_iter = 65
		+ (int)(log(vars->view.scale + 1.0) * 8.0)
		+ vars->aug_iter;
	while (i < vars->max_iter)
	{
		if (z.a * z.a + z.b * z.b > 4.0)
			break ;
		z = (t_cmplx){z.a * z.a - z.b * z.b + c.a, 2 * z.a * z.b + c.b};
		i++;
	}
	fractal_pxl_put(vars, z, point, i);
}
