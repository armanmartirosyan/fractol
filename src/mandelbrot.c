/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armartir <armartir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 16:56:50 by armartir          #+#    #+#             */
/*   Updated: 2023/03/11 12:56:58 by armartir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	param_init_m(t_params	*params)
{
	params->min.r = -2.0;
	params->min.i = -1.5;
	params->max.r = 1.0;
	params->max.i = 1.5;
	params->r = 2;
	params->g = 2;
	params->b = 2;
	params->fractol_type = 1;
}

int	mandelbrot_set(t_complex c, int max_iter)
{
	int			i;
	t_complex	z;
	double		zr;
	double		zi;

	z.r = 0;
	z.i = 0;
	i = 0;
	while (i < max_iter)
	{
		zr = z.r;
		zi = z.i;
		z.r = zr * zr - zi * zi + c.r;
		z.i = 2 * zr * zi + c.i;
		if (z.r * z.r + z.i * z.i > 4)
			break ;
		i++;
	}
	return (i);
}

void	draw_mandelbrot(t_params *p)
{
	int			x;
	int			y;
	t_complex	c;
	char		*addr;

	mlx_clear_window(p->mlx, p->win);
	y = -1;
	while (++y < W_HEIGHT)
	{
		x = -1;
		while (++x < W_WIDTH)
		{	
			c.r = (p->min.r) + (p->max.r - p->min.r) * x / (W_WIDTH - 1.0);
			c.i = (p->min.i) + (p->max.i - p->min.i) * y / (W_HEIGHT - 1.0);
			p->cur_iter = mandelbrot_set(c, MAX_ITERATIONS);
			if (p->cur_iter == MAX_ITERATIONS)
				p->color = create_trgb(1, p->r, p->g, p->b);
			else
				p->color = create_trgb(1, p->r, p->g, p->b) * p->cur_iter;
			addr = p->addr + (y * p->line_len + x
					* (p->bpp / 8));
			*(unsigned int *)addr = p->color;
		}
	}
	mlx_put_image_to_window(p->mlx, p->win, p->img_ptr, 0, 0);
}
