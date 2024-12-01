/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_ops.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 13:31:23 by carlosg2          #+#    #+#             */
/*   Updated: 2024/12/01 18:20:40 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <math.h>

t_cmplx	complex_div(t_cmplx c1, t_cmplx c2)
{
	double	denom;

	denom = c2.a * c2.a + c2.b * c2.b;
	return ((t_cmplx){(c1.a * c2.a + c1.b * c2.b) / denom,
		(c1.b * c2.a - c1.a * c2.b) / denom});
}

t_cmplx	complex_sum(t_cmplx c1, t_cmplx c2)
{
	return ((t_cmplx){c1.a + c2.a, c1.b + c2.b});
}

t_cmplx	complex_mult(t_cmplx c1, t_cmplx c2)
{
	return ((t_cmplx){c1.a * c2.a - c1.b * c2.b, c1.a * c2.b + c1.b * c2.a});
}

t_cmplx	complex_conj(t_cmplx c)
{
	return ((t_cmplx){c.a, -c.b});
}

double	complex_mod(t_cmplx c)
{
	return (sqrt(c.a * c.a + c.b * c.b));
}
