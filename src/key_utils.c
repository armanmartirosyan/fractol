/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armartir <armartir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 11:30:13 by armartir          #+#    #+#             */
/*   Updated: 2023/03/11 11:53:58 by armartir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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

void	zoom_out(t_params *p, double r, double i)
{
	double	width;
	double	height;

	width = p->max.r - p->min.r;
	height = p->max.i - p->min.i;
	width *= 1.5;
	height *= 1.5;
	p->min.r = r - width / 2.0;
	p->min.i = i - height / 2.0;
	p->max.r = r + width / 2.0;
	p->max.i = i + height / 2.0;
}

void	zoom_in(t_params *p, double r, double i)
{
	double	width;
	double	height;

	width = p->max.r - p->min.r;
	height = p->max.i - p->min.i;
	width /= 1.5;
	height /= 1.5;
	p->min.r = r - width / 2.0;
	p->min.i = i - height / 2.0;
	p->max.r = r + width / 2.0;
	p->max.i = i + height / 2.0;
}

void	julia_args_ch(int key, t_params *p)
{
	if (key == KEY_Z)
	p->julia.r += 0.1;
	if (key == KEY_X)
		p->julia.r -= 0.1;
	if (key == KEY_C)
		p->julia.i += 0.1;
	if (key == KEY_V)
		p->julia.i -= 0.1;
}

void	handle_rgb(int key, t_params *p)
{
	if (key == KEY_R)
		p->r += 10;
	else if (key == KEY_G)
		p->g += 10;
	else if (key == KEY_B)
		p->b += 10;
}
