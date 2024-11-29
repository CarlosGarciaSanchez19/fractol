/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colormaps.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 19:27:13 by carlosg2          #+#    #+#             */
/*   Updated: 2024/11/29 16:16:52 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	rainbow_color(int i, t_vars *vars)
{
	int red;
	int green;
	int blue;

	red = (int)(sin(vars->color_freq * 0.16 * i + 4) * 127 + 128);
	green = (int)(sin(vars->color_freq * 0.13 * i + 2) * 127 + 128);
	blue = (int)(sin(vars->color_freq * 0.1 * i + 1) * 127 + 128);
	return ((red << 16) | (green << 8) | blue);
}

int	color_to_color(double t, int color1, int color2)
{
	t_rgbcolor rgb1;
	t_rgbcolor rgb2;

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

int	blue_to_gold_to_red(int i, t_vars *vars)
{
	double		t;
	int			color;
	int			c_group;

	c_group = (int)(NUM_COLORS / vars->color_freq) / 4;
	t = (double)(i % (c_group * 4));
	if (t < c_group)
		color = color_to_color(t / c_group, 0x031967, 0xFFFFFF);
	else if (t >= c_group && t < c_group * 2)
		color = color_to_color((t - c_group) / c_group, 0xFFFFFF, 0xFFCD00);
	else if (t >= c_group * 2 && t < c_group * 3)
		color = color_to_color((t - c_group * 2) / c_group, 0xFFCD00, 0xFF0000);
	else
		color = color_to_color((t - c_group * 3) / c_group, 0xFF0000, 0x031967);
	return (color);
}

int	blue_to_gold(int i, t_vars *vars)
{
	t_rgbcolor	rgb;
	t_rgbcolor	rgb_gold;
	int			blue;
	int			gold;

	blue = 0x000080;
	gold = 0xFFD700;
	rgb.r = (double)get_r(blue);
	rgb.g = (double)get_g(blue);
	rgb.b = (double)get_b(blue);
	rgb_gold.r = (double)get_r(gold);
	rgb_gold.g = (double)get_g(gold);
	rgb_gold.b = (double)get_b(gold);
	rgb.r = (rgb.r + (rgb_gold.r - rgb.r) * fabs(sin(vars->color_freq * 0.1 * i)));
	rgb.g = (rgb.g + (rgb_gold.g - rgb.g) * fabs(sin(vars->color_freq * 0.1 * i)));
	rgb.b = (rgb.b + (rgb_gold.b - rgb.b) * fabs(sin(vars->color_freq * 0.1 * i)));
	return ((int)rgb.r << 16 | (int)rgb.g << 8 | (int)rgb.b);
}

int	red_to_yellow(int i, t_vars *vars)
{
	double	r;
	double	g;
	double	b;
	int		red;

	red = 0xFF0000;
	r = (double)get_r(red);
	g = (double)get_g(red);
	b = (double)get_b(red);
	r = (r + (255.0 - r) * fabs(sin(vars->color_freq * 0.1 * i)));
	g = (g + (255.0 - g) * fabs(sin(vars->color_freq * 0.1 * i)));
	b = (b + (0.0 - b) * fabs(sin(vars->color_freq * 0.1 * i)));
	return ((int)r << 16 | (int)g << 8 | (int)b);
}

int	white_to_color(int i, t_vars *vars)
{
	double	r;
	double	g;
	double	b;
	int		colors[4];

	colors[0] = 0xA9561E;
	colors[1] = 0xAA0000;
	colors[2] = 0x00AA00;
	colors[3] = 0x0000AA;
	r = (double)get_r(colors[vars->colormap_type - 4]);
	g = (double)get_g(colors[vars->colormap_type - 4]);
	b = (double)get_b(colors[vars->colormap_type - 4]);
	r = (r + (255.0 - r) * fabs(sin(vars->color_freq * 0.1 * i)));
	g = (g + (255.0 - g) * fabs(sin(vars->color_freq * 0.1 * i)));
	b = (b + (255.0 - b) * fabs(sin(vars->color_freq * 0.1 * i)));
	return ((int)r << 16 | (int)g << 8 | (int)b);
}

void	color_fill(t_vars *vars, int (*map)(int, t_vars *))
{
	int i;

	i = 0;
	while (i < NUM_COLORS)
	{
		vars->colormap[i] = map(i, vars);
		i++;
	}
}
