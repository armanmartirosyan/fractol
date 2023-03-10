/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armartir <armartir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 19:32:07 by armartir          #+#    #+#             */
/*   Updated: 2023/03/10 16:44:01 by armartir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <unistd.h>
# include <mlx.h>
# include <math.h>
# include "validation.h"
// TODO: Delete stdio library
# include <stdio.h>

# define W_WIDTH 600
# define W_HEIGHT 600
# define MAX_ITERATIONS 500

// KEYS
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_PLUS 24
# define KEY_MINUS 27
# define KEY_ESC 53
# define KEY_R 15
# define KEY_G 5
# define KEY_B 11

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

#endif