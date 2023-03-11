/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atod.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armartir <armartir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 11:24:20 by armartir          #+#    #+#             */
/*   Updated: 2023/03/11 14:54:26 by armartir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	ft_atod(const char *str)
{
	int		pos;
	double	val;
	int		i;
	int		sign;

	i = -1;
	while (str[++i])
		if (!(str[i] >= '0' && str[i] <= '9') && str[i] != '.'
			&& str[i] != '-' && str[i] != '+')
			instructions();
	pos = 0;
	val = 0;
	sign = parse_sign(str, &pos);
	val = parse_integer(str, &pos);
	parse_decimal(str, &pos, &val);
	if (str[pos] != '\0')
		return (0.0);
	pos = 0;
	val *= sign;
	return (val);
}

double	parse_sign(const char *str, int *pos)
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

double	parse_integer(const char *str, int *pos)
{
	double	val;

	val = 0.0;
	while (str[*pos] >= '0' && str[*pos] <= '9')
	{
		val = val * 10.0 + (str[*pos] - '0');
		(*pos)++;
	}
	return (val);
}

double	parse_decimal(const char *str, int *pos, double *val)
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
