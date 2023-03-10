/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armartir <armartir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 19:30:23 by armartir          #+#    #+#             */
/*   Updated: 2023/03/10 16:44:39 by armartir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdlib.h>

void	instructions();

void	choose_fractol(t_params *p);

double parse_sign(const char* str, int* pos);

double parse_integer(const char* str, int* pos);

double parse_decimal(const char* str, int* pos, double* val);

double ft_atom(const char* str)
{
	int		pos;
    double	val;
	int		i;

	i = -1;
	while (str[++i])
		if (!(str[i] >= '0' && str[i] <= '9') && str[i] != '.')
			instructions();
	pos = 0;
	val = 0;
    val = parse_sign(str, &pos) * parse_integer(str, &pos);
    parse_decimal(str, &pos, &val);
    if (str[pos] != '\0')
        return (0.0);
	pos = 0;
	val *= parse_sign(str, &pos);
	return (val);
}

double parse_sign(const char* str, int* pos)
{
    if (str[*pos] == '-')
	{
        (*pos)++;
        return (-1.0);
    }
	else if (str[*pos] == '+')
        (*pos)++;
    return (1.0);
}

double parse_integer(const char* str, int* pos)
{
    double val;

	val = 0.0;
    while (str[*pos] >= '0' && str[*pos] <= '9')
	{
        val = val * 10.0 + (str[*pos] - '0');
        (*pos)++;
    }
    return (val);
}

double parse_decimal(const char* str, int* pos, double* val)
{
	double	decimal;

    if (str[*pos] == '.')
	{
        (*pos)++;
        decimal = 1.0;
        while (str[*pos] >= '0' && str[*pos] <= '9')
		{
            *val = *val * 10.0 + (str[*pos] - '0');
            decimal *= 10.0;
            (*pos)++;
        }
        *val /= decimal;
    }
    return (*val);
}

void	instructions()
{
	write(1, "Use following commands.\n", 24);
	write(1, "Mandelbrot\n", 11);
	write(1, "Julia\n", 7);
	write(1, "Smt\n", 4);
	exit (0);
}

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] >= 'A' && s1[i] <= 'Z')
			s1[i] += 32;
		i++;
	}
	i = 0;
	if (n == 0)
		return (0);
	while (i < n - 1 && s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
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

void	draw_mandelbrot(t_params *params)
{
	int			x;
	int			y;
	t_complex	c;
	char		*addr;

	mlx_clear_window(params->mlx, params->win);
	y = 0;
	while (y < W_HEIGHT)
	{
		x = 0;
		while (x < W_WIDTH)
		{
			c.r = (params->min.r) + (params->max.r - params->min.r) * x / (W_WIDTH - 1.0);
			c.i = (params->min.i) + (params->max.i - params->min.i) * y / (W_HEIGHT - 1.0);
			params->cur_iter = mandelbrot_set(c, MAX_ITERATIONS);
			if (params->cur_iter == MAX_ITERATIONS)
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

int julia_set(t_complex *c, double c_real, double c_imag)
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
        z_new.i = 2 * z_real * z_imag + c_imag;
        z_real = z_new.r;
        z_imag = z_new.i;
        if (z_real * z_real + z_imag * z_imag > 4)
            return (i);
		i++;
	}
    
    return (MAX_ITERATIONS);
}

void	draw_julia(t_params *p)
{
	int			x;
	int			y;
	t_complex	c;
	char		*addr;

	mlx_clear_window(p->mlx, p->win);
	y = 0;
	while (y < W_HEIGHT)
	{
		x = 0;
		while (x < W_WIDTH)
		{
 			// c.r = 0.16 * 4 * ((double)x / W_WIDTH - 0.5);
            // c.i = 0.16 * 4 * ((double)y / W_HEIGHT - 0.5);

			c.r = (p->min.r) + (p->max.r - p->min.r) * x / (W_WIDTH - 1.0);
			c.i = (p->min.i) + (p->max.i - p->min.i) * y / (W_HEIGHT - 1.0);
			p->cur_iter = julia_set (&c, p->julia.r, p->julia.i);
			if (p->cur_iter == MAX_ITERATIONS)
				p->color = create_trgb(1,p->r,p->g,p->b);
			else
				p->color = create_trgb(1,p->r,p->g,p->b) * p->cur_iter;
		 	addr = p->addr + (y * p->line_len + x * (p->bpp / 8));
            *(unsigned int *)addr = p->color;
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(p->mlx, p->win, p->img_ptr, 0, 0);
}

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

void	param_init_j(t_params	*params, char *av2, char *av3)
{
	params->julia.r = ft_atom(av2);
	params->julia.i = ft_atom(av3);
	params->min.r = -2.0;
	params->min.i = -1.5;
	params->max.r = 2.0;
	params->max.i = 1.5;
	params->r = 50;
	params->g = 50;
	params->b = 50;
	params->fractol_type = 2;
	if (params->julia.r < -2.0 || params->julia.r > 2.0 ||
		params->julia.i < -2.0 || params->julia.i > 2.0)
		instructions();
}

void	zoom_out_m(t_params *p, double r, double i)
{
	double width;
    double height;

	width = p->max.r - p->min.r;
	height = p->max.i - p->min.i;
	width *= 1.5;
    height *= 1.5;
    p->min.r = r - width / 2.0;
    p->min.i = i - height / 2.0;
    p->max.r = r + width / 2.0;
    p->max.i = i + height / 2.0;
}

void	zoom_in_m(t_params *p, double r, double i)
{
	double width;
    double height;

	width = p->max.r - p->min.r;
	height = p->max.i - p->min.i;
	width /= 1.5;
    height /= 1.5;
    p->min.r = r - width / 2.0;
    p->min.i = i - height / 2.0;
    p->max.r = r + width / 2.0;
    p->max.i = i + height / 2.0;
}

int	zoom(int key,int x,int y,t_params *p)
{
	t_complex	center;
	
	center.r = (p->min.r) + (p->max.r - p->min.r) * x / (W_WIDTH - 1.0);
	center.i = (p->min.i) + (p->max.i - p->min.i) * y / (W_HEIGHT - 1.0);
	if (key == MOUSE_DOWN)
		zoom_out_m(p, center.r, center.i);
	if (key == MOUSE_UP)
		zoom_in_m(p, center.r, center.i);

	choose_fractol(p);
	return (0);
}

void	key_arrows(int key, t_params *p)
{
	double	x;
	double	y;

	x = p->max.r - p->min.r;
	y = p->max.i - p->min.i;
	if (key == KEY_RIGHT)
	{	
	p->min.r += x * 0.1;
	p->max.r += x * 0.1;
	}
	else if (key == KEY_LEFT)
	{	
	p->min.r -= x * 0.1;
	p->max.r -= x * 0.1;
	}
	else if (key == KEY_DOWN)
	{	
	p->min.i += y * 0.1;
	p->max.i += y * 0.1;
	}
	else if (key == KEY_UP)
	{	
	p->min.i -= y * 0.1;
	p->max.i -= y * 0.1;
	}
}

int	get_key(int key, t_params *p)
{
	t_complex	center;

	center.r = (p->min.r) + (p->max.r - p->min.r) * (W_WIDTH / 2) / (W_WIDTH - 1.0);
	center.i = (p->min.i) + (p->max.i - p->min.i) * (W_HEIGHT / 2) / (W_HEIGHT - 1.0);
	if (key == KEY_ESC)
	{
		mlx_destroy_window(p->mlx, p->win);
		exit(0);
	}
	if (key == KEY_R)
		p->r += 10;
	else if (key == KEY_G)
		p->g += 10;
	else if (key == KEY_B)
		p->b += 10;
	else if (key == KEY_PLUS)
		zoom_in_m (p, center.r, center.i);
	else if (key == KEY_MINUS)
		zoom_out_m(p, center.r, center.i);
	else 
		key_arrows(key, p);
	choose_fractol(p);
	return (0);
}

void	open_win(t_params *params, char *av)
{
	params->mlx = mlx_init();
	params->win = mlx_new_window(params->mlx, W_HEIGHT, W_WIDTH, av);
	params->img_ptr = mlx_new_image(params->mlx, W_WIDTH, W_HEIGHT);
	params->addr = mlx_get_data_addr(params->img_ptr, &params->bpp, &params->line_len, &params->endian);
}

void	choose_fractol(t_params *p)
{
	if (p->fractol_type == 1)
		draw_mandelbrot(p);
	if (p->fractol_type == 2)
		draw_julia(p);
}

void	validation(char **av)
{
	t_params	params;

	if (!(ft_strncmp(av[1], "mandelbrot", 10)))
		param_init_m(&params);
	else if (!(ft_strncmp(av[1], "julia", 5)) && av[2] && av[3])
		param_init_j(&params,av[2],av[3]);
	else if ( !av[2] && !(ft_strncmp(av[1], "julia", 5)))
		param_init_j(&params,"-0.8","0.156");
	else
		instructions();
	open_win(&params, av[1]);
	choose_fractol(&params);
	mlx_mouse_hook(params.win, zoom,&params);
	mlx_key_hook(params.win, get_key, &params);
	mlx_loop(params.mlx);
}

int main (int argc, char **argv)
{

	if (argc < 2 || argc > 4)
		instructions();
	validation(argv);

	return (0);
}
