/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armartir <armartir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 19:30:23 by armartir          #+#    #+#             */
/*   Updated: 2023/03/05 15:32:41 by armartir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// int rgb_to_int(double r, double g, double b)
// {
//     int color = 0;
//     color |= (int)(b * 255);
//     color |= (int)(g * 255) << 8;
//     color |= (int)(r * 255) << 16;
//     return (color);
// }

// void	mandelbrod(double x,double y)
// {
// 	double	zx;
// 	double	zy;
// 	double	tmp;
// 	int		iter;

// 	iter = 0;
// 	zx = x;
// 	zy = y;
// 	while (pow(x,2) + pow(y, 2) < 4 && iter < 50)
// 	{
// 		tmp = x;
// 		x = pow(x, 2) + pow(y, 2) + zx;
// 		y = 2 * y * tmp + zy;
// 	}
	
	
// }

// void	my_mlx_pixel_put (t_data *data, int x, int y, int color)
// {
// 	char	*dst;

// 	dst = data->addr + (y * data->line_lenght + x * (data->bits_per_pixel / 8));
// 	*(unsigned int*)dst = color;
// }

// int main()
// {
// 	void	*mlx_ptr;
// 	void	*win_ptr;
// 	t_data	img;
// 	double i = -500;
// 	double j = 0;
// 	const double height = 1920;
// 	const double width = 1080;


// 	mlx_ptr = mlx_init();
// 	win_ptr = mlx_new_window(mlx_ptr, 1920, 1080, "Hello World");
// 	img.img = mlx_new_image(mlx_ptr, 1920, 1080);

// 	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_lenght, &img.endian);

// 	while (i < height)
// 	{
// 		j = -500;
// 		while (j < width)
// 		{
// 			if (pow(i,2) + pow(j,2) <= pow (120,2))
// 				mlx_pixel_put(mlx_ptr, win_ptr, j + height/2, i + width/2, 0x00FFFFFF);
// 			// my_mlx_pixel_put(&img, i, j, 0x00FF0000);
// 			j++;
// 		}
// 		i++;
// 	}

// 	// mlx_put_image_to_window(mlx_ptr, win_ptr, img.img, 0, 0);
// 	mlx_loop(mlx_ptr);
// 	return (0);
// }

#include "mlx.h"
#include <math.h>
#include <stdlib.h>

typedef struct s_complex
{
    double r;
    double i;
} t_complex;

typedef struct s_params
{
    void *mlx;
    void *win;
    void *img;
    char *addr;
    int bpp;
    int line_len;
    int endian;
    int width;
    int height;
    t_complex min;
    t_complex max;
    int max_iterations;
} t_params;

int mandelbrot(t_complex c, int max_iterations)
{
    int i;
    t_complex z;
    z.r = 0;
    z.i = 0;

    for (i = 0; i < max_iterations; i++)
    {
        double zr = z.r;
        double zi = z.i;
        z.r = zr * zr - zi * zi + c.r;
        z.i = 2 * zr * zi + c.i;
        if (z.r * z.r + z.i * z.i > 4)
            break;
    }
    return i;
}

void draw_fractal(t_params *params)
{
    int x, y;
    t_complex c;
    int color;

    for (y = 0; y < params->height; y++)
    {
        for (x = 0; x < params->width; x++)
        {
            c.r = params->min.r + (params->max.r - params->min.r) * x / (params->width - 1.0);
            c.i = params->min.i + (params->max.i - params->min.i) * y / (params->height - 1.0);

            int iterations = mandelbrot(c, params->max_iterations);

            if (iterations == params->max_iterations)
                color = 0x000000;
            else
                color = 0x0000FF * (iterations % 256);

            char *pixel_addr = params->addr + (y * params->line_len + x * (params->bpp / 8));
            *(unsigned int *)pixel_addr = color;
        }
    }
    mlx_put_image_to_window(params->mlx, params->win, params->img, 0, 0);
}

int main()
{
    t_params params;
    params.width = 1080;
    params.height = 1080;
    params.min.r = -2.0;
    params.max.r = 1.0;
    params.min.i = -1.2;
    params.max.i = 1.2;
    params.max_iterations = 50;

    params.mlx = mlx_init();
    params.win = mlx_new_window(params.mlx, params.width, params.height, "Mandelbrot");
    params.img = mlx_new_image(params.mlx, params.width, params.height);
    params.addr = mlx_get_data_addr(params.img, &params.bpp, &params.line_len, &params.endian);

    draw_fractal(&params);

    mlx_loop(params.mlx);
    return 0;
}

