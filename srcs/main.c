#include "../incls/mini_rt.h"
#include "../libft/libsrcs/libft.h"
#include "../libft/libsrcs/ft_printf.h"
#include "../libft/libsrcs/get_next_line.h"
#include "../libx/mlx.h"

#include <stdio.h>

void remake_scene(t_scene *scene, t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx->img = mlx_new_image(mlx->mlx, mlx->width, mlx->height);
	ray_tracing(scene, 0, 0);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}

int get_hit_color(t_scene *scene, t_ray ray)
{
	size_t	i;
	double distance;
	double closer;
	int		color;	
	t_shape *obj;

	closer = M_INFINITY;
	color = 0xFFFFFF;
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

t_ray	ray_generator(t_scene *scene, int x, int y)
{
	t_vec3	shooting_direction;
	t_ray	ray;

	shooting_direction = ray_pixel_to_world(scene, x, y);
	shooting_direction = multiply_by_matrix(shooting_direction, scene->cam->m);
	shooting_direction = vec_sub(shooting_direction, scene->cam->origin);
	shooting_direction = vec_normalize(shooting_direction);
	ray = ray_settings(scene->cam->origin, shooting_direction);
	return(ray);
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

void	make_scene(t_scene *scene)
{
	t_mlx	*mlx;

	mlx = get_mlx();
	ray_tracing(scene, 0, 0);
	hook_collection(mlx, scene);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	mlx_loop(mlx->mlx);
}

int	main (int argc, char **argv)
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


	// int sample = 0;
	// while (sample < 1)
	// {
	// 	printf("-----------------------------------------\n");
	// 	// printf("cam ori x = %f\n", scene->cam->origin.x);
	// 	// printf("cam ori y = %f\n", scene->cam->origin.y);
	// 	// printf("cam ori z = %f\n", scene->cam->origin.z);
	// 	// printf("Fichier .rt cam dir x = %f\n", scene->cam->dir.x);
	// 	// printf("Fichier .rt cam dir y = %f\n", scene->cam->dir.y);
	// 	// printf("Fichier .rt cam dir z = %f\n", scene->cam->dir.z);
		
	// 	// printf("\v");

	// 	// printf("ray direction x = %f\n", ray.direction.x);
	// 	// printf("ray direction y = %f\n", ray.direction.y);
	// 	// printf("ray direction z = %f\n", ray.direction.z);
	// 	// printf("\v");
	// 	// printf("ray origin x = %f\n", ray.origin.x);
	// 	// printf("ray origin y = %f\n", ray.origin.y);
	// 	// printf("ray origin z = %f\n", ray.origin.z);
	// 	printf("-----------------------------------------\n");
	// 	sample++;
	// }