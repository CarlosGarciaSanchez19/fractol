/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 13:46:30 by carlosg2          #+#    #+#             */
/*   Updated: 2024/11/29 13:45:05 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int interpolate_color(int color1, int color2, double t)
{
    int red = ((1 - t) * ((color1 >> 16) & 0xFF)) + (t * ((color2 >> 16) & 0xFF));
    int green = ((1 - t) * ((color1 >> 8) & 0xFF)) + (t * ((color2 >> 8) & 0xFF));
    int blue = ((1 - t) * (color1 & 0xFF)) + (t * (color2 & 0xFF));
    return ((red << 16) | (green << 8) | blue);
}

int get_interpolated_color(int i, int max_iter)
{
    double t;

	t = (double)i / max_iter;
    return interpolate_color(0x0000FF, 0xFF0000, t); // De azul a rojo
}

void	mandelbrot(t_vars *vars, t_cmplx c, t_point point)
{
	int		i;
	t_cmplx	z;

	z = (t_cmplx){0, 0};
	i = 0;
	vars->max_iter = 180 + (int)(log(vars->view.scale + 1.0) * 8.0) + vars->aug_iter;
	while (i < vars->max_iter)
	{
		if (z.a * z.a + z.b * z.b > 4.0)
			break ;
		z = (t_cmplx){z.a * z.a - z.b * z.b + c.a, 2 * z.a * z.b + c.b};
		i++;
	}
	fractal_pixel_put(vars, z, point, i);
}
