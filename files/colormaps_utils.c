/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colormaps_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 20:43:22 by carlosg2          #+#    #+#             */
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

int	get_t(int trgb)
{
	return ((trgb >> 24) & 0xFF);
}

int	get_r(int trgb)
{
	return ((trgb >> 16) & 0xFF);
}

int	get_g(int trgb)
{
	return ((trgb >> 8) & 0xFF);
}

int	get_b(int trgb)
{
	return (trgb & 0xFF);
}

int	color_to_color(double t, int color1, int color2)
{
	t_rgbcolor	rgb1;
	t_rgbcolor	rgb2;

	rgb1.r = (double)get_r(color1);
	rgb1.g = (double)get_g(color1);
	rgb1.b = (double)get_b(color1);
	rgb2.r = (double)get_r(color2);
	rgb2.g = (double)get_g(color2);
	rgb2.b = (double)get_b(color2);
	rgb1.r = (rgb1.r + (rgb2.r - rgb1.r) * fabs(sin(t)));
	rgb1.g = (rgb1.g + (rgb2.g - rgb1.g) * fabs(sin(t)));
	rgb1.b = (rgb1.b + (rgb2.b - rgb1.b) * fabs(sin(t)));
	return ((int)rgb1.r << 16 | (int)rgb1.g << 8 | (int)rgb1.b);
}
