/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_creation_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadia <jbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 17:07:59 by tshimoda          #+#    #+#             */
/*   Updated: 2022/03/25 11:10:56 by jbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incls/mini_rt.h"

t_matrix	new_matrix(t_vec3 origin, t_vec3 forward, t_vec3 right, t_vec3 up)
{
	t_matrix	new;

	new.d[0][0] = right.x;
	new.d[0][1] = right.y;
	new.d[0][2] = right.z;
	new.d[0][3] = 0;
	new.d[1][0] = up.x;
	new.d[1][1] = up.y;
	new.d[1][2] = up.z;
	new.d[1][3] = 0;
	new.d[2][0] = forward.x;
	new.d[2][1] = forward.y;
	new.d[2][2] = forward.z;
	new.d[2][3] = 0;
	new.d[3][0] = origin.x;
	new.d[3][1] = origin.y;
	new.d[3][2] = origin.z;
	new.d[3][3] = 1;
	return (new);
}

t_matrix	matrix_identity(void)
{
	t_scene	*scene;
	t_vec3	forward;
	t_vec3	up;
	t_vec3	right;
	t_vec3	origin;

	scene = get_scene();
	forward = new_vector(0, 0, 1);
	right = new_vector(0, 0, 1);
	up = new_vector(0, 1, 0);
	origin = new_vector(0, 0, 0);
	return (new_matrix(origin, forward, right, up));
}

void	matrix_look_at(t_scene *s)
{
	t_vec3		random;
	t_vec3		right;
	t_vec3		up;

	random = new_vector(0, 1, 0);
	right = vec_cross(random, s->cam->dir);
	right = vec_normalize(right);
	up = vec_cross(s->cam->dir, right);
	up = vec_normalize(up);
	s->cam->m.d[0][0] = right.x;
	s->cam->m.d[0][1] = right.y;
	s->cam->m.d[0][2] = right.z;
	s->cam->m.d[0][3] = 0;
	s->cam->m.d[1][0] = up.x;
	s->cam->m.d[1][1] = up.y;
	s->cam->m.d[1][2] = up.z;
	s->cam->m.d[1][3] = 0;
	s->cam->m.d[2][0] = s->cam->dir.x;
	s->cam->m.d[2][1] = s->cam->dir.y;
	s->cam->m.d[2][2] = s->cam->dir.z;
	s->cam->m.d[2][3] = 0;
	s->cam->m.d[3][0] = s->cam->origin.x;
	s->cam->m.d[3][1] = s->cam->origin.y;
	s->cam->m.d[3][2] = s->cam->origin.z;
	s->cam->m.d[3][3] = 1;
}
