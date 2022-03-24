/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadia <jbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 12:24:46 by tshimoda          #+#    #+#             */
/*   Updated: 2022/03/24 15:10:04 by jbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incls/mini_rt.h"

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
