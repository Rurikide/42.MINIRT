/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadia <jbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 12:29:32 by tshimoda          #+#    #+#             */
/*   Updated: 2022/03/24 15:07:50 by jbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incls/mini_rt.h"
#include "../libft/libsrcs/libft.h"
#include "../libx/mlx.h"
#include <stdio.h>

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
		if (distance > 0 && distance < closer)
		{
			closer = distance;
			color = get_color(obj, ray, scene, distance);
		}
		i++;
	}
	return (color);
}

t_ray	ray_generator(t_scene *scene, int x, int y)
{
	t_vec3	shooting_direction;
	t_ray	ray;

	shooting_direction = ray_pixel_to_world(scene, x, y);
	shooting_direction = multiply_by_matrix(shooting_direction, scene->cam->m);
	shooting_direction = vec_sub(shooting_direction, scene->cam->origin);
	shooting_direction = vec_normalize(shooting_direction);
	ray = ray_settings(scene->cam->origin, shooting_direction);
	return (ray);
}

void	ray_tracing(t_scene *scene, int x, int y)
{
	t_mlx	*mlx;
	t_ray	ray;
	int		color;

	mlx = get_mlx();
	matrix_look_at(scene);
	while (y < mlx->height)
	{
		x = 0;
		while (x < mlx->width)
		{
			ray = ray_generator(scene, x, y);
			color = get_hit_color(scene, ray);
			my_mlx_pixel_put(mlx, x, y, color);
			x++;
		}
		y++;
	}
}

int	main(int argc, char **argv)
{
	t_scene	*scene;

	if (argc != 2)
	{
		printf("Error\n");
		printf("Please select onr .rt file\n");
		exit(EXIT_FAILURE);
	}
	scene = get_scene();
	parse_machine(scene, argv[1]);
	make_scene(scene);
	return (0);
}
