/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 19:15:09 by carlosg2          #+#    #+#             */
/*   Updated: 2024/11/29 16:21:10 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

typedef struct __attribute__((packed)) {
    uint16_t file_type;    // Tipo de archivo, siempre 'BM' (0x4D42)
    uint32_t file_size;    // Tamaño del archivo en bytes
    uint16_t reserved1;    // Reservado (debe ser 0)
    uint16_t reserved2;    // Reservado (debe ser 0)
    uint32_t offset_data;  // Offset desde el inicio del archivo hasta los datos de la imagen
    uint32_t size;         // Tamaño del encabezado de información (40 bytes)
    int32_t width;         // Anchura de la imagen
    int32_t height;        // Altura de la imagen (positiva para bottom-up)
    uint16_t planes;       // Número de planos de color (siempre 1)
    uint16_t bit_count;    // Bits por píxel (24 para BMP)
    uint32_t compression;  // Tipo de compresión (0 para sin compresión)
    uint32_t size_image;   // Tamaño de los datos de la imagen (puede ser 0 para imágenes sin compresión)
    int32_t x_pixels_per_meter; // Resolución horizontal
    int32_t y_pixels_per_meter; // Resolución vertical
    uint32_t colors_used;       // Número de colores en la paleta (0 para imágenes de 24 bits)
    uint32_t colors_important;  // Número de colores importantes (0 para todas)
} BMPHeader;

// Función para guardar la imagen
void	save_image_as_bmp(t_vars *vars, const char *filename)
{
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("Error opening file");
        return;
    }

    // Obtener datos de la imagen
    char *data = vars->img.addr;

    // Crear encabezado BMP
    BMPHeader header = {0};
    header.file_type = 0x4D42; // 'BM'
    header.file_size = sizeof(BMPHeader) + vars->img.line_length * HEIGHT;
    header.offset_data = sizeof(BMPHeader);
    header.size = 40;
    header.width = WIDTH;
    header.height = -HEIGHT; // Top-down BMP
    header.planes = 1;
    header.bit_count = 24; // 24 bits (RGB)
    header.compression = 0;

    // Escribir encabezado
    ssize_t bytes_written;
	bytes_written = write(fd, &header, sizeof(header));
	if (bytes_written != sizeof(header))
	{
    	perror("Error while writing BMP header");
    	close(fd);
    	return;
	}

    // Escribir los datos de los píxeles (BMP utiliza BGR)
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            int pixel = *(int *)(data + (y * vars->img.line_length + x * vars->img.bits_per_pixel / 8));
            char b = (pixel & 0xFF);
            char g = (pixel >> 8) & 0xFF;
            char r = (pixel >> 16) & 0xFF;
            bytes_written = write(fd, &b, 1);
            bytes_written = write(fd, &g, 1);
            bytes_written = write(fd, &r, 1);
        }
    }

    close(fd);
    printf("Image saved as %s\n", filename);
}
