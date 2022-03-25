/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   click_event_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadia <jbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 17:04:39 by tshimoda          #+#    #+#             */
/*   Updated: 2022/03/25 11:10:13 by jbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incls/mini_rt.h"

t_shape	*get_hit_shape(t_scene *scene, t_ray ray)
{
	size_t	i;
	double	distance;
	double	closer;
	t_shape	*shape;
	t_shape	*obj;

	closer = INFINITY;
	shape = NULL;
	i = 0;
	while (i < scene->objs->total)
	{
		obj = (t_shape *)scene->objs->elements[i];
		distance = obj->hit_obj(obj->shape, ray.origin, ray.direction);
		if (distance > M_EPSILON && distance < closer)
		{
			closer = distance;
			shape = obj;
		}
		i++;
	}
	if (shape == NULL)
		return (NULL);
	return (shape);
}

int	click_event(int button, int x, int y, t_scene *scene)
{
	t_shape	*clic;
	t_ray	ray;

	ray = ray_generator(scene, x, y);
	clic = get_hit_shape(scene, ray);
	if (clic == NULL || button == MOUSE_RIGHT)
		scene->screen.is_selected = NONE;
	if (clic == NULL || button == MOUSE_RIGHT)
		scene->select = NULL;
	else if (clic->type == SP)
	{
		printf("Sphere selected\n");
		sphere_resize(button, scene, clic);
	}
	else if (clic->type == PL)
	{
		printf("Plane selected\n");
		plane_event(scene, clic);
	}
	else if (clic->type == CY)
	{
		printf("Cylinder selected\n");
		cylinder_event(button, scene, clic);
	}
	return (0);
}
