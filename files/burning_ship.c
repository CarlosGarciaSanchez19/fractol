/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burning_ship.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:23:04 by carlosg2          #+#    #+#             */
/*   Updated: 2024/12/05 11:02:27 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	burning_ship(t_vars *vars, t_cmplx c, t_point point)
{
	int		i;
	t_cmplx	z;
	double	abs_z_a;
	double	abs_z_b;
	int		max_iter;

	z = (t_cmplx){0, 0};
	i = 0;
	max_iter = 40 + (int)(log(vars->view.scale + 1.0) * 8.0)
		+ vars->aug_iter;
	while (i < max_iter)
	{
		if (z.a * z.a + z.b * z.b > 4.0)
			break ;
		abs_z_a = fabs(z.a);
		abs_z_b = fabs(z.b);
		z = (t_cmplx){abs_z_a * abs_z_a - abs_z_b * abs_z_b + c.a,
			2 * abs_z_a * abs_z_b + c.b};
		i++;
	}
	fractal_pxl_put(vars, z, point, (t_point){i, max_iter});
}
