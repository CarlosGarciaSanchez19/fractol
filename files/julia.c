/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:57:08 by carlosg2          #+#    #+#             */
/*   Updated: 2024/12/04 13:10:38 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	julia_cosh(t_vars *vars, t_cmplx z, t_point point)
{
	int		i;
	t_cmplx	c;

	c = (t_cmplx){-0.45, 0.0};
	i = 0;
	vars->max_iter += vars->aug_iter;
	while (i < vars->max_iter)
	{
		if (z.a * z.a + z.b * z.b > 4.0)
			break ;
		z = (t_cmplx){cosh(z.a) * cos(z.b) + c.a, sinh(z.a) * sin(z.b) + c.b};
		i++;
	}
	fractal_pxl_put(vars, z, point, i);
}

void	julia(t_vars *vars, t_cmplx z, t_point point)
{
	int		i;
	t_cmplx	c;

	c = vars->c;
	vars->max_iter = 100
		+ (int)(log(vars->view.scale + 5.0) * 8.0)
		+ vars->aug_iter;
	i = 0;
	while (i < vars->max_iter)
	{
		if (z.a * z.a + z.b * z.b > 4.0)
			break ;
		z = (t_cmplx){z.a * z.a - z.b * z.b + c.a, 2 * z.a * z.b + c.b};
		i++;
	}
	fractal_pxl_put(vars, z, point, i);
}
