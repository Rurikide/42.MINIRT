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
	// aka intersection
	int	i;
	double distance;
	double closer;
	int		color;	
	t_shape *obj;

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

t_ray		ray_settings(t_vec3 origin, t_vec3 direction)
{
	t_ray result;

	result.origin = origin;
	result.direction = direction;
	return (result);
}

t_vec3		ray_to_pixel(t_scene *scene, int x, int y)
{
	double fov_coeff;
	double aspect_ratio;
	double p_x;
	double p_y;

	fov_coeff = tanf((double)scene->cam->fov / 2 * M_PI / 180);
	aspect_ratio = (double)get_mlx()->width / (double)get_mlx()->height;
	p_x = (2 * (x + 0.5) / (double)get_mlx()->width - 1) * aspect_ratio * fov_coeff;
	p_y = (1 - 2 * (y + 0.5) / (double)get_mlx()->height) * fov_coeff;

	// jai mis -p_x
	return (new_vector(-p_x, p_y, 1));
}

t_ray	ray_generator(t_scene *scene, int x, int y)
{
	t_ray ray;
	t_vec3 dir;

	dir = ray_to_pixel(scene, x, y);
	dir = multiply_by_matrix(dir, scene->cam->m);
	dir = vec_sub(dir, scene->cam->origin);
	dir = vec_normalize(dir);
	ray = ray_settings(scene->cam->origin, dir);
	return(ray);
}

void	ray_tracing(t_scene *scene, int x, int y)
{
	t_mlx	*mlx;
	t_ray	ray;
	int		color;

	mlx = get_mlx();
	scene->cam->m = matrix_look_at(scene->cam->origin, scene->cam->dir);
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

int main (int argc, char **argv)
 {
 	t_scene *scene;

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