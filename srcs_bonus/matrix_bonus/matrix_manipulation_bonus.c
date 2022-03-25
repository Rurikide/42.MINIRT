/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_manipulation_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadia <jbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 17:08:08 by tshimoda          #+#    #+#             */
/*   Updated: 2022/03/25 11:11:01 by jbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incls/mini_rt.h"

t_matrix	matrix_rot_x(double degrees)
{
	t_matrix	rotate;
	double		radians;

	radians = degrees * M_PI / 180;
	rotate = matrix_identity();
	rotate.d[1][1] = cosf(radians);
	rotate.d[1][2] = -sinf(radians);
	rotate.d[2][1] = sinf(radians);
	rotate.d[2][2] = cosf(radians);
	return (rotate);
}

t_matrix	matrix_rot_y(double degrees)
{
	t_matrix	rotate;
	double		radians;

	radians = degrees * M_PI / 180;
	rotate = matrix_identity();
	rotate.d[0][0] = cosf(radians);
	rotate.d[0][2] = sinf(radians);
	rotate.d[2][0] = -sinf(radians);
	rotate.d[2][2] = cosf(radians);
	return (rotate);
}

t_matrix	matrix_product(t_matrix src, t_matrix mult)
{
	static t_matrix	res;
	int				i;
	int				j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			res.d[i][j] = src.d[i][0] * mult.d[0][j] + \
			src.d[i][1] * mult.d[1][j] \
			+ src.d[i][2] * mult.d[2][j] + src.d[i][3] * mult.d[3][j];
			j++;
		}
		i++;
	}
	return (res);
}

t_vec3	multiply_by_matrix(t_vec3 p, t_matrix m)
{
	t_vec3	res;

	res.x = p.x * m.d[0][0] + p.y * m.d[1][0] + p.z * m.d[2][0] + m.d[3][0];
	res.y = p.x * m.d[0][1] + p.y * m.d[1][1] + p.z * m.d[2][1] + m.d[3][1];
	res.z = p.x * m.d[0][2] + p.y * m.d[1][2] + p.z * m.d[2][2] + m.d[3][2];
	return (res);
}
