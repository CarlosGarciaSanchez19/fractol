/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_funct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 20:05:42 by carlosg2          #+#    #+#             */
/*   Updated: 2024/11/26 18:14:24 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/* t_cmplx	cmplx_cosh(t_cmplx z) 
{
    t_cmplx	result;
    double	exp_real = exp(z.a);
    double	exp_neg_real = exp(-z.a);

    result.a = (exp_real + exp_neg_real) / 2 * cos(z.b);
    result.b = (exp_real - exp_neg_real) / 2 * sin(z.b);
    return (result);
} */

t_cmplx	cmplx_sinh(t_cmplx c)
{
	return ((t_cmplx){sinh(c.a) * cos(c.a), (cosh(c.b) * sin(c.b))});
}

t_cmplx	cmplx_cosh(t_cmplx c)
{
	return ((t_cmplx){cosh(c.a) * cos(c.b), sinh(c.a) * sin(c.b)});
}
