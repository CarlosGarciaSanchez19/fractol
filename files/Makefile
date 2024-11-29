# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/21 15:51:39 by carlosg2          #+#    #+#              #
#    Updated: 2024/11/28 19:28:19 by carlosg2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

BNAME = fractol_bonus

SRCS = complex_ops.c mandelbrot.c complex_funct.c julia.c \
	   fractol_utils.c fractol_utils2.c fractol_utils3.c \
	   taylor_series.c colormaps.c colormaps_utils.c burning_ship.c \
	   save_image.c \

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror -g

%.o: %.c
	$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@

$(NAME): $(OBJS) fractol.c
	$(CC) $(CFLAGS) $(OBJS) fractol.c -LLibft -lft -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

bonus: $(BNAME)

$(BNAME): $(OBJS) fractol_bonus.c
	$(CC) $(CFLAGS) $(OBJS) fractol_bonus.c -LLibft -lft -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(BNAME)

all: $(NAME)

clean:
	rm -f $(OBJS) fractol_bonus.o fractol.o

fclean: clean
	rm -f $(NAME) $(BNAME)

re: fclean all

.PHONY: all clean fclean re
