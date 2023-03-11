/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armartir <armartir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 19:30:23 by armartir          #+#    #+#             */
/*   Updated: 2023/03/11 17:31:54 by armartir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	close_win(t_params *p)
{
	mlx_clear_window(p->mlx, p->win);
	mlx_destroy_image(p->mlx, p->img_ptr);
	mlx_destroy_window(p->mlx, p->win);
	exit (0);
	return (0);
}

void	open_win(t_params *params, char *av)
{
	params->mlx = mlx_init();
	params->win = mlx_new_window(params->mlx, W_HEIGHT, W_WIDTH, av);
	params->img_ptr = mlx_new_image(params->mlx, W_WIDTH, W_HEIGHT);
	params->addr = mlx_get_data_addr(params->img_ptr,
			&params->bpp, &params->line_len, &params->endian);
}

void	choose_fractol(t_params *p)
{
	if (p->fractol_type == 1)
		draw_mandelbrot(p);
	if (p->fractol_type == 2)
		draw_julia(p);
	if (p->fractol_type == 3)
		draw_burning(p);
}

void	validation(char **av)
{
	t_params	params;

	if (ft_strncmp(av[1], "mandelbrot", ft_strlen(av[1])) == 0 && !av[2])
		param_init_m(&params);
	else if (ft_strncmp(av[1], "julia", ft_strlen(av[1])) == 0
		&& av[2] && av[3])
		param_init_j(&params, av[2], av[3]);
	else if (ft_strncmp(av[1], "julia", ft_strlen(av[1])) == 0 && !av[2])
		param_init_j(&params, "-0.8", "0.156");
	else if (ft_strncmp(av[1], "burningship", ft_strlen(av[1])) == 0 && !av[2])
		param_init_b(&params);
	else
		instructions();
	open_win(&params, av[1]);
	choose_fractol(&params);
	mlx_mouse_hook(params.win, zoom, &params);
	mlx_key_hook(params.win, get_key, &params);
	mlx_hook(params.win, 17, 1L << 17, close_win, &params);
	mlx_loop(params.mlx);
}

int	main(int argc, char **argv)
{
	if (argc < 2 || argc > 4)
		instructions();
	validation(argv);
	return (0);
}
