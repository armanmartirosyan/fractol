/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armartir <armartir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 19:32:07 by armartir          #+#    #+#             */
/*   Updated: 2023/03/05 16:57:03 by armartir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

#include <unistd.h>
#include <mlx.h>
#include <math.h>
// TODO: Delete stdio library
#include <stdio.h>

# define W_WIDTH 1080
# define W_HEIGHT 1080
# define MAX_ITERATIONS 50
typedef struct s_complex
{
	double	r;
	double	i;
}	t_complex;

typedef struct s_params
{
	void		*mlx;
	void		*win;
	void		*img_ptr;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
	int			width;
	int			height;
	t_complex	min;
	t_complex	max;
	int			scale;
	int			max_iter;
	int			color;
	int			cur_iter;
}	t_params;


#endif