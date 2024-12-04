# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/21 15:51:39 by carlosg2          #+#    #+#              #
#    Updated: 2024/12/04 13:12:24 by carlosg2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

SRCS = mandelbrot.c julia.c key_press_management.c \
	fractol_utils.c fractol_utils2.c fractol_utils3.c \
	colormaps.c colormaps_utils.c colormaps_utils2.c \
	burning_ship.c save_image.c parse_input_print_opt.c \
	init_vars_mse_zoom.c fractol.c

OBJS = $(SRCS:.c=.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror -O3

LIBRARIES = -LLibft -lft -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBRARIES) -o $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
