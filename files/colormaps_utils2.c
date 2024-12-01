/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colormaps_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 17:43:30 by carlosg2          #+#    #+#             */
/*   Updated: 2024/12/01 17:44:20 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	color_fill(t_vars *vars, int (*map)(int, t_vars *))
{
	int	i;

	i = 0;
	while (i < NUM_COLORS)
	{
		vars->colormap[i] = map(i, vars);
		i++;
	}
}
