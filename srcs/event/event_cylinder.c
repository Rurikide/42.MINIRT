/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 17:04:59 by tshimoda          #+#    #+#             */
/*   Updated: 2022/03/18 17:06:27 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incls/mini_rt.h"

void	cylinder_event(int button, t_scene *scene, t_shape *clic)
{
	t_cy	*cylinder;

	scene->screen.is_selected = CY;
	scene->select = clic;
	cylinder = (t_cy *)clic->shape;
	if (button == ROULETTE_FORWARD)
	{
		cylinder->rad += 0.5;
		remake_scene(scene, get_mlx());
	}
	if (button == ROULETTE_BACKWARD)
	{
		if (cylinder->rad > 0.5)
			cylinder->rad -= 0.5;
		remake_scene(scene, get_mlx());
	}
}

void	cylinder_height(int keycode, t_scene *scene)
{
	t_cy	*cylinder;

	if (scene->screen.is_selected == CY)
		cylinder = ((t_cy *)scene->select->shape);
	else
		return ;
	if (keycode == KEY_PLUS)
			cylinder->height += 1;
	else if (keycode == KEY_MINUS && cylinder->height > 1)
			cylinder->height -= 1;
	remake_scene(scene, get_mlx());
}

void	cylinder_rotation(int keycode, t_scene *scene)
{
	t_vec3		*cyl_dir;
	double		rot_step;

	cyl_dir = &((t_cy *)scene->select->shape)->dir;
	rot_step = 0.09;
	if (keycode == KEY_PLUS_GRAND)
	{
		if (scene->screen.obj_rot_axis == X_AXIS && cyl_dir->x <= 0.9)
			cyl_dir->x += rot_step;
		else if (scene->screen.obj_rot_axis == Y_AXIS && cyl_dir->y <= 0.9)
			cyl_dir->y += rot_step;
		else if (scene->screen.obj_rot_axis == Z_AXIS && cyl_dir->z <= 0.9)
			cyl_dir->z += rot_step;
	}	
	else if (keycode == KEY_PLUS_PETIT)
	{
		if (scene->screen.obj_rot_axis == X_AXIS && cyl_dir->x >= -0.8)
			cyl_dir->x -= rot_step;
		else if (scene->screen.obj_rot_axis == Y_AXIS && cyl_dir->y >= -0.9)
			cyl_dir->y -= rot_step;
		else if (scene->screen.obj_rot_axis == Z_AXIS && cyl_dir->z >= -0.9)
			cyl_dir->z -= rot_step;
	}
	remake_scene(scene, get_mlx());
}
