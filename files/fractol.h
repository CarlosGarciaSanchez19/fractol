/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlosg2 <carlosg2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 13:58:07 by carlosg2          #+#    #+#             */
/*   Updated: 2024/11/29 15:21:32 by carlosg2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACT_OL_H
# define FRACT_OL_H
# include "mlx_linux/mlx.h"
# include "Libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <pthread.h>
# include <math.h>
# include <stdio.h>


#ifndef NUM_COLORS
# define NUM_COLORS 500
#endif

#ifndef WIDTH
# define WIDTH 1920
#endif

#ifndef HEIGHT
# define HEIGHT 1080
#endif

#ifndef THREADS
# define THREADS sysconf(_SC_NPROCESSORS_ONLN)
#endif

#define MLX_SYNC_IMAGE_WRITABLE		1
#define MLX_SYNC_WIN_FLUSH_CMD		2
#define MLX_SYNC_WIN_CMD_COMPLETED	3

#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct	s_view {
	double	x_min;
	double	x_max;
	double	y_min;
	double	y_max;
	double	scale;
}				t_view;

typedef struct	s_cmplx {
	double	a;
	double	b;
}				t_cmplx;

typedef struct	s_point
{
	int x;
	int y;
}				t_point;

typedef struct s_limits
{
	double *min;
	double *max;
}	t_limits;

typedef struct s_rgbcolor
{
	double	r;
	double	g;
	double	b;
} t_rgbcolor;

typedef struct	s_vars {
	void	*mlx;
	void	*win;
	int		*colormap;
	t_data	img;
	t_view	view;
	int		max_iter;
	int		aug_iter;
	int		mse_is_down;
	int		precision;
	int		colormap_type;
	double	color_freq;
	char	*fractal;
	t_cmplx	c;
}				t_vars;

typedef struct s_thread_data {
    t_vars *vars;
    int start_y;
    int end_y;
} t_thread_data;

enum e_colors
{
	RAINBOW,
	BLUE_TO_GOLD_TO_RED,
	RED_TO_YELLOW,
	BLUE_TO_GOLD,
	WHITE_TO_SIENA,
	WHITE_TO_RED,
	WHITE_TO_GREEN,
	WHITE_TO_BLUE
};

enum e_fractals
{
	MANDELBROT,
	JULIA,
	BURNING_SHIP,
	JULIA_COSH
};

void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
void		fractal_pixel_put(t_vars *vars, t_cmplx z, t_point point, int out_iter);
void		save_image_as_bmp(t_vars *vars, const char *filename);
void		init_vars(t_vars *vars, char **fractal);
/* void		put_circle(t_data *img, t_vars *vars, int color); */
void		adjust_aspect_ratio(t_vars *vars, double asp_ratio);
int			close_window(t_vars *vars);
int			red_to_yellow(int i, t_vars *vars);
int			blue_to_gold(int i, t_vars *vars);
int			blue_to_gold_to_red(int i, t_vars *vars);
int			mouse_zoom(int button, int x, int y, t_vars *vars);
int			mouse_down(t_cmplx mouse, t_vars *vars);
int			mouse_up(int button, int x, int y, t_vars *vars);
void		mse_julia_adjust(t_vars *vars);
int			key(int keycode, t_vars *vars);
int			print_key(int keycode, t_vars *vars);
int			render_next_frame(t_vars *vars);
int			trgb(int t, int r, int g, int b);
void		mandelbrot(t_vars *vars, t_cmplx c, t_point point);
void		julia(t_vars *vars, t_cmplx c, t_point point);
void		burning_ship(t_vars *vars, t_cmplx c, t_point point);
void		julia_cosh(t_vars *vars, t_cmplx c, t_point point);
int			get_t(int trgb);
int			get_r(int trgb);
int			get_g(int trgb);
int			get_b(int trgb);
int			rainbow_color(int i, t_vars *vars);
int			white_to_color(int i, t_vars *vars);
void		color_fill(t_vars *vars, int (*map)(int, t_vars *));
double		from_int_to_real(int i, double min, double max, int size);
t_cmplx		complex_div(t_cmplx c1, t_cmplx c2);
t_cmplx		complex_sum(t_cmplx c1, t_cmplx c2);
t_cmplx		complex_mult(t_cmplx c1, t_cmplx c2);
t_cmplx		complex_conj(t_cmplx c);
double		complex_mod(t_cmplx c);
double		factorial(int n);
double		s_cos(double x);
double		s_sin(double x);
double		s_cosh(double x);
double		s_sinh(double x);
t_cmplx		cmplx_cosh(t_cmplx z);
t_cmplx		cmplx_sinh(t_cmplx z);

#endif
