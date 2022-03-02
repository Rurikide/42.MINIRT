/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_settings.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 15:24:44 by tshimoda          #+#    #+#             */
/*   Updated: 2022/02/26 15:24:45 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incls/mini_rt.h"

double	parse_dimension(char *line, int *i)
{
	double	measure;
	int		index;
	int		float_len;

	index = *i;
	measure = 0;
	check_if_missing_value(line, index);
	float_len = get_float_len(line, index);
	measure = ft_atod(&line[index]);
	if (measure < 0.0)
		print_error_exit(get_scene(), "negative length");
	*i = index + float_len;
	return (measure);
}

double	parse_light_ratio(char *line, int *i)
{
	double	ratio;
	int		index;
	int		float_len;

	index = *i;
	ratio = 0;
	check_if_missing_value(line, index);
	float_len = get_float_len(line, index);
	ratio = ft_atod(&line[index]);
	if (ratio < 0.0 || ratio > 1.0)
		print_error_exit(get_scene(), "light ratio range");
	*i = index + float_len;
	return (ratio);
}

int	parse_field_of_view(char *line, int *i)
{
	int	index;
	int	value;
	int	fov_len;

	index = *i;
	check_if_missing_value(line, index);
	fov_len = get_int_len(line, index);
	value = ft_atoi(&line[index]);
	if (value < 0 || value > 180)
		print_error_exit(get_scene(), "fov range");
	*i = index + fov_len;
	return (value);
}