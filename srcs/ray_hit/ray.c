/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 12:24:46 by tshimoda          #+#    #+#             */
/*   Updated: 2022/03/21 13:47:47 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incls/mini_rt.h"

int	get_hit_color(t_scene *scene, t_ray ray)
{
	size_t	i;
	double	distance;
	double	closer;
	int		color;	
	t_shape	*obj;

	closer = M_INFINITY;
	color = 0x000000;
	i = 0;
	while (i < scene->objs->total)
	{
		obj = (t_shape *)scene->objs->elements[i];
		distance = obj->hit_obj(obj->shape, ray.origin, ray.direction);
		if (distance >= M_EPSILON && distance < closer)
		{
			closer = distance;
			color = get_color(obj, ray, scene, distance);
		}
		i++;
	}
	return (color);
}

t_ray	ray_settings(t_vec3 origin, t_vec3 direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = direction;
	return (ray);
}

t_vec3	ray_pixel_to_world(t_scene *scene, int x, int y)
{
	double	aspect_ratio;
	double	fov;
	double	p_x;
	double	p_y;

	fov = tanf((double)scene->cam->fov / 2 * M_PI / 180);
	aspect_ratio = (double)get_mlx()->width / (double)get_mlx()->height;
	p_x = (2 * (x + 0.5) / (double)get_mlx()->width - 1) * aspect_ratio * fov;
	p_y = (1 - 2 * (y + 0.5) / (double)get_mlx()->height) * fov;
	return (new_vector(-p_x, p_y, 1));
}
