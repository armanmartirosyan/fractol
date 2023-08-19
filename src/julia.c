/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armartir <armartir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 11:07:45 by armartir          #+#    #+#             */
/*   Updated: 2023/03/11 14:54:02 by armartir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	param_init_j(t_params	*params, char *av2, char *av3)
{
	params->julia.r = ft_atod(av2);
	params->julia.i = ft_atod(av3);
	params->min.r = -2.0;
	params->min.i = -1.5;
	params->max.r = 2.0;
	params->max.i = 1.5;
	params->r = 50;
	params->g = 50;
	params->b = 50;
	params->fractol_type = 2;
	if (!(params->julia.r >= -2.0 && params->julia.r <= 2.0)
		|| !(params->julia.i >= -2.0 && params->julia.i <= 2.0))
		instructions();
}

void	draw_julia(t_params *p)
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
			p->cur_iter = julia_set (&c, p->julia.r, p->julia.i);
			if (p->cur_iter == MAX_ITERATIONS)
				p->color = create_trgb(1, p->r, p->g, p->b);
			else
				p->color = create_trgb(1, p->r, p->g, p->b) * p->cur_iter;
			addr = p->addr + (y * p->line_len + x * (p->bpp / 8));
			*(unsigned int *)addr = p->color;
		}
	}
	mlx_put_image_to_window(p->mlx, p->win, p->img_ptr, 0, 0);
}

int	julia_set(t_complex *c, double c_real, double c_imag)
{
	double		z_real;
	double		z_imag;
	t_complex	z_new;
	int			i;

	i = 0;
	z_real = c->r;
	z_imag = c->i;
	while (i < MAX_ITERATIONS)
	{
		z_new.r = z_real * z_real - z_imag * z_imag + c_real;
		z_new.i = 2 * z_real * z_imag - c_imag;
		z_real = z_new.r;
		z_imag = z_new.i;
		if (z_real * z_real + z_imag * z_imag > 4)
			return (i);
		i++;
	}
	return (MAX_ITERATIONS);
}
