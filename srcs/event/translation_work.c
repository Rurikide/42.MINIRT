/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation_work.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 17:53:14 by tshimoda          #+#    #+#             */
/*   Updated: 2022/03/21 14:05:19 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incls/mini_rt.h"

void	key_translation_ad(int keycode, t_scene *scene, t_vec3 *origin)
{
	t_vec3	move;

	move.x = scene->cam->m.d[0][0];
	move.y = scene->cam->m.d[0][1];
	move.z = scene->cam->m.d[0][2];
	move = vec_multiply(move, STEP);
	if (keycode == KEY_A)
	{
		origin->x += move.x;
		origin->y += move.y;
		origin->z += move.z;
	}
	else if (keycode == KEY_D)
	{
		origin->x -= move.x;
		origin->y -= move.y;
		origin->z -= move.z;
	}
	remake_scene(scene, get_mlx());
}

void	key_translation_ws(int keycode, t_scene *scene, t_vec3 *origin)
{
	t_vec3	move;

	move.x = scene->cam->m.d[2][0];
	move.y = scene->cam->m.d[2][1];
	move.z = scene->cam->m.d[2][2];
	move = vec_multiply(move, STEP);
	if (keycode == KEY_W)
	{
		origin->x += move.x;
		origin->y += move.y;
		origin->z += move.z;
	}
	else if (keycode == KEY_S)
	{
		origin->x -= move.x;
		origin->y -= move.y;
		origin->z -= move.z;
	}
	remake_scene(scene, get_mlx());
}

void	key_translation_rt(int keycode, t_scene *scene, t_vec3 *origin)
{
	t_vec3	move;

	move.x = scene->cam->m.d[1][0];
	move.y = scene->cam->m.d[1][1];
	move.z = scene->cam->m.d[1][2];
	move = vec_multiply(move, STEP);
	if (keycode == KEY_T)
	{
		origin->x += move.x;
		origin->y += move.y;
		origin->z += move.z;
	}
	else if (keycode == KEY_R)
	{
		origin->x -= move.x;
		origin->y -= move.y;
		origin->z -= move.z;
	}
	remake_scene(scene, get_mlx());
}
