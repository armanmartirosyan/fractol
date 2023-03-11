/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armartir <armartir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 16:43:41 by armartir          #+#    #+#             */
/*   Updated: 2023/03/11 11:40:30 by armartir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDATION_H
# define VALIDATION_H

// Arguments parsing
double	parse_sign(const char *str, int *pos);
double	parse_integer(const char *str, int *pos);
double	parse_decimal(const char *str, int *pos, double *val);
double	ft_atod(const char *str);

// Instructions
void	instructions(void);

// Validation
void	validation(char **av);

#endif