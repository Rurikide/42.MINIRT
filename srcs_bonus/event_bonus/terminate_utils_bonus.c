/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadia <jbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 17:31:49 by tshimoda          #+#    #+#             */
/*   Updated: 2022/03/25 11:10:43 by jbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incls/mini_rt.h"

void	*free_shape(void *object)
{
	t_shape	*sh;

	if (object == NULL)
		return (NULL);
	sh = (t_shape *)object;
	free(sh->shape);
	return (NULL);
}

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

void	close_minirt(void)
{
	t_mlx	*mlx;

	mlx = get_mlx();
	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx_destroy_window(mlx->mlx, mlx->win);
	free_scene(get_scene());
	exit(0);
}

int	click_close_window(void)
{
	printf("clicked the red (x)\n");
	close_minirt();
	return (0);
}

void	print_error_exit(t_scene *scene, char *msg)
{
	ft_putendl_fd("Error", 1);
	ft_putendl_fd(msg, 1);
	if (scene != NULL)
		free_scene(scene);
	exit(EXIT_FAILURE);
}
