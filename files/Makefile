# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/21 15:51:39 by carlosg2          #+#    #+#              #
#    Updated: 2024/12/04 14:30:48 by carlosg2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

CFLAGS = -Wall -Wextra -Werror -O3

CC = gcc $(CFLAGS)

SRCS = mandelbrot.c julia.c key_press_management.c \
	fractol_utils.c fractol_utils2.c fractol_utils3.c \
	colormaps.c colormaps_utils.c colormaps_utils2.c \
	burning_ship.c save_image.c parse_input_print_opt.c \
	init_vars_mse_zoom.c fractol.c

OBJS = $(SRCS:.c=.o)

LIBRARIES = -LLibft -lft -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBRARIES) -o $(NAME)
	@echo "fractol compiled successfully!"

all: $(NAME)

clean_images:
	@rm -f *.bmp
	@echo "Images removed"

clean:
	@rm -f $(OBJS)
	@echo "Objects removed"

fclean: clean
	@rm -f $(NAME)
	@echo "fractol removed"

re: fclean all

.PHONY: all clean fclean re clean_images
