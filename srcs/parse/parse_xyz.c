/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_xyz.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 15:26:59 by tshimoda          #+#    #+#             */
/*   Updated: 2022/03/10 20:33:31 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incls/mini_rt.h"

void	check_unit_range(t_vec3 *unit)
{
	if (unit->x < -1.0 || unit->x > 1.0)
		print_error_exit(get_scene(), "unit range");
	if (unit->y < -1.0 || unit->y > 1.0)
		print_error_exit(get_scene(), "unit range");
	if (unit->z < -1.0 || unit->z > 1.0)
		print_error_exit(get_scene(), "unit range");
	if (unit->y == 1)
	{
		if (unit->x == 0 && unit->z == 0)
			unit->x = 0.000001;
	}
	else if (unit->y == -1)
	{
		if (unit->x == 0 && unit->z == 0)
			unit->x = -0.000001;
	}
}

double	parse_1coord_xyz(char *line, int *i)
{
	int		coord_len;
	double	value;
	int		index;

	index = *i;
	check_if_missing_value(line, index);
	coord_len = get_float_len(line, index);
	value = ft_atod(&line[index]);
	*i = index + coord_len;
	return (value);
}

void	set_coord_xyz(t_vec3 *v, char *line, int *i)
{
	v->x = parse_1coord_xyz(line, i);
	check_if_missing_comma(line, i);
	v->y = parse_1coord_xyz(line, i);
	check_if_missing_comma(line, i);
	v->z = parse_1coord_xyz(line, i);
}
