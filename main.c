/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armartir <armartir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 19:30:23 by armartir          #+#    #+#             */
/*   Updated: 2023/03/09 14:49:44 by armartir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdlib.h>

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	mandelbrot(t_complex c, int max_iter)
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

void	draw_fractol(t_params *params)
{
	int			x;
	int			y;
	t_complex	c;
	char		*addr;

	mlx_clear_window(params->mlx, params->win);
	y = 0;
	while (y < params->height)
	{
		x = 0;
		while (x < params->width)
		{
			c.r = (params->min.r) + (params->max.r - params->min.r) * x / (params->width - 1.0);
			c.i = (params->min.i) + (params->max.i - params->min.i) * y / (params->height - 1.0);

			params->cur_iter = mandelbrot(c, params->max_iter);
			if (params->cur_iter == params->max_iter)
				params->color = create_trgb(1,params->r,params->g,params->b);
			else
				params->color = create_trgb(1,params->r,params->g,params->b) * params->cur_iter;
		 	addr = params->addr + (y * params->line_len + x * (params->bpp / 8));
            *(unsigned int *)addr = params->color;
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(params->mlx, params->win, params->img_ptr, 0, 0);
}

void	param_init(t_params	*params)
{
	params->width = W_WIDTH;
	params->height = W_HEIGHT;
	params->min.r = -2.0;
	params->min.i = -1.5;
	params->max.r = 1.0;
	params->max.i = 1.5;
	params->max_iter = MAX_ITERATIONS;
	params->r = 2;
	params->g = 2;
	params->b = 2;
}

int	zoom(int key,int x,int y,t_params *p)
{
	t_complex	center;
	
	center.r = (p->min.r) + (p->max.r - p->min.r) * x / (p->width - 1.0);
	center.i = (p->min.i) + (p->max.i - p->min.i) * y / (p->height - 1.0);
    double width = p->max.r - p->min.r;
    double height = p->max.i - p->min.i;
	if (key == MOUSE_DOWN)
	{
	width *= 1.5;
    height *= 1.5;

    p->min.r = center.r - width / 2.0;
    p->min.i = center.i - height / 2.0;

    p->max.r = center.r + width / 2.0;
    p->max.i = center.i + height / 2.0;
	draw_fractol(p);
	}
	if (key == MOUSE_UP)
	{

    width /= 1.5;
    height /= 1.5;

    p->min.r = center.r - width / 2.0;
    p->min.i = center.i - height / 2.0;

    p->max.r = center.r + width / 2.0;
    p->max.i = center.i + height / 2.0;
	draw_fractol(p);
	}
	return (0);
}

int	get_key(int key, t_params *p)
{
	if (key == KEY_ESC)
	{
		mlx_destroy_window(p->mlx, p->win);
		exit(0);
	}
	if (key == KEY_R)
		p->r += 10;
	if (key == KEY_G)
		p->g += 10;
	if (key == KEY_B)
		p->b += 10;

	if (key == KEY_PLUS)
	{	
	p->min.r *= 1.5;
	p->min.i *= 1.5;
	p->max.r *= 1.5;
	p->max.i *= 1.5;
	}
	if (key == KEY_MINUS)
	{	
	p->min.r /= 1.5;
	p->min.i /= 1.5;
	p->max.r /= 1.5;
	p->max.i /= 1.5;
	}
	if (key == KEY_RIGHT)
	{	
	p->min.r += 0.5;
	p->max.r += 0.5;
	}
	if (key == KEY_LEFT)
	{	
	p->min.r -= 0.5;
	p->max.r -= 0.5;
	}
	if (key == KEY_DOWN)
	{	
	p->min.i += 0.5;
	p->max.i += 0.5;
	}
	if (key == KEY_UP)
	{	
	p->min.i -= 0.5;
	p->max.i -= 0.5;
	}
	draw_fractol(p);
	return (0);
}

int main ()
{
	t_params	params;

	param_init(&params);
	params.mlx = mlx_init();
	params.win = mlx_new_window(params.mlx, params.height, params.width, "Mandelbrot");
	params.img_ptr = mlx_new_image(params.mlx, params.width, params.height);
	params.addr = mlx_get_data_addr(params.img_ptr, &params.bpp, &params.line_len, &params.endian);

	draw_fractol(&params);
	mlx_mouse_hook(params.win, zoom,&params);
	mlx_key_hook(params.win, get_key, &params);
	
	mlx_loop(params.mlx);
	return (0);
}

