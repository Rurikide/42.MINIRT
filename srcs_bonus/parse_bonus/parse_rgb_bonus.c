/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rgb_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadia <jbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 15:24:06 by tshimoda          #+#    #+#             */
/*   Updated: 2022/03/25 11:11:26 by jbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incls/mini_rt.h"

void	check_rgb_range(int r, int g, int b)
{
	if (r < 0 || r > 255)
		print_error_exit(get_scene(), "rgb range");
	if (g < 0 || g > 255)
		print_error_exit(get_scene(), "rgb range");
	if (b < 0 || b > 255)
		print_error_exit(get_scene(), "rgb range");
}

int	parse_1color_rgb(char *line, int *i)
{
	int	rgb_len;
	int	value;
	int	index;

	index = *i;
	check_if_missing_value(line, index);
	rgb_len = get_int_len(line, index);
	value = ft_atoi(&line[index]);
	*i = index + rgb_len;
	return (value);
}

void	set_color_rgb(t_rgb *color, char *line, int *i)
{
	color->r = parse_1color_rgb(line, i);
	check_if_missing_comma(line, i);
	color->g = parse_1color_rgb(line, i);
	check_if_missing_comma(line, i);
	color->b = parse_1color_rgb(line, i);
	check_rgb_range(color->r, color->g, color->b);
}
