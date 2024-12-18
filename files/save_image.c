/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 19:15:09 by carlosg2          #+#    #+#             */
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

static void	init_header(t_vars *vars, t_BMPHeader *header)
{
	header->file_type = 0x4D42;
	header->file_size = sizeof(t_BMPHeader) + vars->img.line_length * HEIGHT;
	header->offset_data = sizeof(t_BMPHeader);
	header->size = 40;
	header->width = WIDTH;
	header->height = -HEIGHT;
	header->planes = 1;
	header->bit_count = 24;
	header->compression = 0;
	header->size_image = WIDTH * abs(HEIGHT) * 3;
}

static void	write_pixels_into_image(t_vars *vars, int fd)
{
	char		*data;
	t_point		pt;
	t_bgrcolor	color;
	int			pixel;
	ssize_t		bytes_written;

	bytes_written = 0;
	data = vars->img.addr;
	pt.y = 0;
	while (pt.y++ < HEIGHT)
	{
		pt.x = 0;
		while (pt.x < WIDTH)
		{
			pixel = *(int *)(data
					+ (pt.y * vars->img.line_length
						+ (pt.x++) * vars->img.bits_per_pixel / 8));
			color.b = (pixel & 0xFF);
			color.g = (pixel >> 8) & 0xFF;
			color.r = (pixel >> 16) & 0xFF;
			bytes_written = write(fd, &color, 3);
			if (bytes_written < 0)
				return (close(fd), perror("Error while writing BMP data"));
		}
	}
}

void	save_image_as_bmp(t_vars *vars, const char *filename)
{
	int			fd;
	ssize_t		bytes_written;
	t_BMPHeader	header;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("Error opening file");
		return ;
	}
	init_header(vars, &header);
	bytes_written = write(fd, &header, sizeof(header));
	if (bytes_written != sizeof(header))
	{
		perror("Error while writing BMP header");
		close(fd);
		return ;
	}
	write_pixels_into_image(vars, fd);
	close(fd);
	ft_printf("Image saved as %s\n", filename);
}
