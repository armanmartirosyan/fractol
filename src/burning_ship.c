/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burning_ship.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armartir <armartir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 12:50:46 by armartir          #+#    #+#             */
/*   Updated: 2023/03/11 17:31:19 by armartir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	param_init_b(t_params	*params)
{
	params->min.r = -2.0;
	params->min.i = -1.5;
	params->max.r = 1.0;
	params->max.i = 1.5;
	params->r = 2;
	params->g = 2;
	params->b = 2;
	params->fractol_type = 3;
}

int	burning_set(t_complex *c)
{
	double	cr;
	double	ci;
	double	cr2;
	int		m;

	m = 0;
	cr = 0;
	ci = 0;
	while (m < MAX_ITERATIONS)
	{
		cr = fabs(cr);
		ci = fabs(ci);
		cr2 = cr;
		cr = cr * cr - ci * ci + c->r;
		ci = 2.0 * cr2 * ci + c->i;
		m++;
		if (cr * cr + ci * ci > 4)
			break ;
	}
	return (m);
}

void	draw_burning(t_params *p)
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
			p->cur_iter = burning_set(&c);
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
