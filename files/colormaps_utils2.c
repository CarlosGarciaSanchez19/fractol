/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colormaps_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 17:43:30 by carlosg2          #+#    #+#             */
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
