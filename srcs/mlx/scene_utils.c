/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 15:27:08 by tshimoda          #+#    #+#             */
/*   Updated: 2022/03/18 14:32:50 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incls/mini_rt.h"

void	free_scene(t_scene *scene)
{
	if (scene->amb != NULL)
		free(scene->amb);
	if (scene->cam != NULL)
		free(scene->cam);
	if (scene->lit != NULL)
		free(scene->lit);
	if (scene->objs != NULL)
		vector_free_elements(scene->objs, free_shape);
}

t_scene	*get_scene(void)
{
	static t_scene	scene;

	if (scene.init != 1)
	{
		scene.init = 1;
		scene.amb = NULL;
		scene.cam = NULL;
		scene.lit = NULL;
		scene.select = NULL;
		scene.screen.x = 0;
		scene.screen.y = 0;
		scene.screen.is_selected = 0;
		scene.screen.obj_rot_axis = X_AXIS;
		scene.objs = ft_calloc(1, sizeof(t_vector));
		vector_init_array(scene.objs);
	}
	return (&scene);
}

void	free_shape(void * object)
{
	t_shape *sh;

	if (object == NULL)
		return;
	sh = (t_shape *)object;
	free(sh->shape);
}