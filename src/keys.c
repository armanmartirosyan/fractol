/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armartir <armartir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 11:29:11 by armartir          #+#    #+#             */
/*   Updated: 2023/03/11 17:14:23 by armartir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	get_key(int key, t_params *p)
{
	t_complex	center;

	center.r = (p->min.r) + (p->max.r - p->min.r)
		* (W_WIDTH / 2) / (W_WIDTH - 1.0);
	center.i = (p->min.i) + (p->max.i - p->min.i)
		* (W_HEIGHT / 2) / (W_HEIGHT - 1.0);
	if (key == KEY_Z || key == KEY_X || key == KEY_C || key == KEY_V)
		julia_args_ch(key, p);
	else if (key == KEY_ESC)
	{
		mlx_destroy_window(p->mlx, p->win);
		exit(0);
	}
	else if (key == KEY_R || key == KEY_G || key == KEY_B)
		handle_rgb (key, p);
	else if (key == KEY_PLUS)
		zoom_in (p, center.r, center.i);
	else if (key == KEY_MINUS)
		zoom_out(p, center.r, center.i);
	else
		key_arrows(key, p);
	choose_fractol(p);
	return (0);
}

int	zoom(int key, int x, int y, t_params *p)
{
	t_complex	center;

	center.r = (p->min.r) + (p->max.r - p->min.r) * x / (W_WIDTH - 1.0);
	center.i = (p->min.i) + (p->max.i - p->min.i) * y / (W_HEIGHT - 1.0);
	if (key == MOUSE_DOWN)
		zoom_out(p, center.r, center.i);
	if (key == MOUSE_UP)
		zoom_in(p, center.r, center.i);
	choose_fractol(p);
	return (0);
}
