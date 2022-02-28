/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 15:27:08 by tshimoda          #+#    #+#             */
/*   Updated: 2022/02/26 15:27:08 by tshimoda         ###   ########.fr       */
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
		vector_free_elements(scene->objs);
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
		scene.objs = ft_calloc(1, sizeof(t_vector));
		vector_init_array(scene.objs);
	}
	return (&scene);
}
