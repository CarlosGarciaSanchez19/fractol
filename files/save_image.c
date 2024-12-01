/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 19:15:09 by carlosg2          #+#    #+#             */
/*   Updated: 2024/12/01 18:47:26 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
}

static void	write_pixels_into_image(t_vars *vars, int fd)
{
	char		*data;
	t_rgbcolor	color;
	int			x;
	int			y;
	int			pixel;

	data = vars->img.addr;
	y = 0;
	while (y++ < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			pixel = *(int *)(data
					+ (y * vars->img.line_length
						+ x * vars->img.bits_per_pixel / 8));
			color.b = (pixel & 0xFF);
			color.g = (pixel >> 8) & 0xFF;
			color.r = (pixel >> 16) & 0xFF;
			write(fd, &color.b, 1);
			write(fd, &color.g, 1);
			write(fd, &color.r, 1);
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
