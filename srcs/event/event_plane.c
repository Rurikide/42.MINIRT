/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadia <jbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 17:06:46 by tshimoda          #+#    #+#             */
/*   Updated: 2022/03/24 15:41:15 by jbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incls/mini_rt.h"

void	plane_event(t_scene *scene, t_shape *clic)
{
	t_pl	*plane;

	scene->screen.is_selected = PL;
	scene->select = clic;
	plane = (t_pl *)clic->shape;
	remake_scene(scene, get_mlx());
}

void	plane_rotation(int keycode, t_scene *scene)
{
	t_vec3	*plane_dir;
	double	rot_step;

	plane_dir = &((t_pl *)scene->select->shape)->dir;
	rot_step = 0.09;
	if (keycode == KEY_PLUS_GRAND)
	{
		if (scene->screen.obj_rot_axis == X_AXIS && plane_dir->x <= 0.9)
			plane_dir->x += rot_step;
		else if (scene->screen.obj_rot_axis == Y_AXIS && plane_dir->y <= 0.9)
			plane_dir->y += rot_step;
		else if (scene->screen.obj_rot_axis == Z_AXIS && plane_dir->z <= 0.9)
			plane_dir->z += rot_step;
	}	
	else if (keycode == KEY_PLUS_PETIT)
	{
		if (scene->screen.obj_rot_axis == X_AXIS && plane_dir->x >= -0.9)
			plane_dir->x -= rot_step;
		else if (scene->screen.obj_rot_axis == Y_AXIS && plane_dir->y >= -0.9)
			plane_dir->y -= rot_step;
		else if (scene->screen.obj_rot_axis == Z_AXIS && plane_dir->z >= -0.9)
			plane_dir->z -= rot_step;
	}
	remake_scene(scene, get_mlx());
}
