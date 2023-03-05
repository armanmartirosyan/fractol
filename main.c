/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armartir <armartir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 19:30:23 by armartir          #+#    #+#             */
/*   Updated: 2023/03/05 17:16:14 by armartir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
/*
for each pixel (Px, Py) on the screen do
    x0 := scaled x coordinate of pixel (scaled to lie in the Mandelbrot X scale (-2.00, 0.47))
    y0 := scaled y coordinate of pixel (scaled to lie in the Mandelbrot Y scale (-1.12, 1.12))
    x := 0.0
    y := 0.0
    iteration := 0
    max_iteration := 1000
    while (x*x + y*y ≤ 2*2 AND iteration < max_iteration) do
        xtemp := x*x - y*y + x0
        y := 2*x*y + y0
        x := xtemp
        iteration := iteration + 1
    
    color := palette[iteration]
    plot(Px, Py, color)
*/

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

	y = 0;
	while (y < params->height)
	{
		x = 0;
		while (x < params->width)
		{
			c.r = params->min.r + (params->max.r - params->min.r) * x / (params->width - 1.0);
			c.i = params->min.i + (params->max.i - params->min.i) * y / (params->height - 1.0);

			params->cur_iter = mandelbrot(c, params->max_iter);
			// if (params->cur_iter == params->max_iter)
			// 	params->color = 0x000000;
			// else
				params->color = 0x0000FF * 50 * params->cur_iter;
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
	mlx_loop(params.mlx);
	return (0);
}

