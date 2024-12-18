/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:58:19 by carlosg2          #+#    #+#             */
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


#include "libft.h"

int	ft_putstr_fd(char *s, int fd)
{
	if (!s)
	{
		write(fd, "(null)", 6);
		return (6);
	}
	else
		write(fd, s, ft_strlen(s));
	return (ft_strlen(s));
}
