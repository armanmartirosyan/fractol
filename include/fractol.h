/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armartir <armartir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 19:32:07 by armartir          #+#    #+#             */
/*   Updated: 2023/03/11 17:32:12 by armartir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <unistd.h>
# include <mlx.h>
# include <math.h>
# include "validation.h"
# include <stdlib.h>

# define W_WIDTH 1000
# define W_HEIGHT 1000
# define MAX_ITERATIONS 1000

// KEYS
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_PLUS 61
# define KEY_MINUS 45
# define KEY_ESC 65307
# define KEY_R 114
# define KEY_G 103
# define KEY_B 98
# define KEY_Z 122
# define KEY_X 120
# define KEY_C 99
# define KEY_V 118

// MOUSE
# define MOUSE_UP 4
# define MOUSE_DOWN 5

typedef struct s_complex
{
	double	r;
	double	i;
}	t_complex;

typedef struct s_params
{
	void					*mlx;
	void					*win;
	void					*img_ptr;
	char					*addr;
	int						bpp;
	int						line_len;
	int						endian;
	t_complex				min;
	t_complex				max;
	int						scale;
	int						color;
	int						cur_iter;
	unsigned char			r;
	unsigned char			g;
	unsigned char			b;
	short					fractol_type;
	char					*name;
	t_complex				julia;
}	t_params;

// Fractol Utils
void	choose_fractol(t_params *p);
void	draw_mandelbrot(t_params *params);
void	param_init_m(t_params	*params);
int		mandelbrot_set(t_complex c, int max_iter);
void	param_init_j(t_params	*params, char *av2, char *av3);
int		julia_set(t_complex *c, double c_real, double c_imag);
void	draw_julia(t_params *p);
void	julia_args_ch(int key, t_params *p);
void	handle_rgb(int key, t_params *p);
void	param_init_b(t_params	*params);
int		burning_set(t_complex *c);
void	draw_burning(t_params *p);

// Utils
int		ft_strncmp(char *s1, char *s2, size_t n);
int		create_trgb(int t, int r, int g, int b);
int		zoom(int key, int x, int y, t_params *p);
void	zoom_in(t_params *p, double r, double i);
void	zoom_out(t_params *p, double r, double i);
void	key_arrows(int key, t_params *p);
int		get_key(int key, t_params *p);
void	open_win(t_params *params, char *av);
int		ft_strlen(const char *s);

#endif