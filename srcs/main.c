#include "../incls/mini_rt.h"
#include "../libft/libsrcs/libft.h"
#include "../libft/libsrcs/ft_printf.h"
#include "../libft/libsrcs/get_next_line.h"
#include "../libx/mlx.h"

#include <stdio.h>

int get_hit_color(t_scene *scene, t_ray ray)
{
	// aka intersection
	int	i;
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

t_vec3		multiply_by_matrix(t_vec3 p, t_matrix m)
 {
 	t_vec3 res;
 	//	p = position d'origine actuelle de la camera. m = matrice [0]Right [1]Up [2]CamDir [3]CamOrigin
 	res.x = p.x * m.d[0][0] + p.y * m.d[1][0] + p.z * m.d[2][0] + m.d[3][0];
 	res.y = p.x * m.d[0][1] + p.y * m.d[1][1] + p.z * m.d[2][1] + m.d[3][1];
 	res.z = p.x * m.d[0][2] + p.y * m.d[1][2] + p.z * m.d[2][2] + m.d[3][2];
 	return (res);
}

t_matrix	look_at(t_vec3 cam_ori, t_vec3 cam_dir)
{
	t_matrix	m;
	t_vec3		random;
	t_vec3		right;
	t_vec3		up;
	t_vec3 forward;
	if (cam_dir.y == 1)
	{
		if (cam_dir.x == 0 && cam_dir.z == 0 )
			cam_dir.x = 0.000001;
	}
	else if (cam_dir.y == -1)
	{
		if (cam_dir.x == 0 && cam_dir.z == 0)
			cam_dir.x = -0.000001;
	}
	random = new_vector(0, 1, 0);
	random = vec_normalize(random);
	right = vec_cross(random, cam_dir);
	right = vec_normalize(right);
	up = vec_cross(cam_dir, right);
	up = vec_normalize(up);
	m.d[0][0] = right.x;
	m.d[0][1] = right.y;
	m.d[0][2] = right.z;
	m.d[0][3] = 0;
	m.d[1][0] = up.x;
	m.d[1][1] = up.y;
	m.d[1][2] = up.z;
	m.d[1][3] = 0;
	m.d[2][0] = cam_dir.x;
	m.d[2][1] = cam_dir.y;
	m.d[2][2] = cam_dir.z;
	m.d[2][3] = 0;
	m.d[3][0] = cam_ori.x;
	m.d[3][1] = cam_ori.y;
	m.d[3][2] = cam_ori.z;
	m.d[3][3] = 1;
	return (m);
}



// t_vec3	add_3_vec(t_vec3 u, t_vec3 v, t_vec3 w)
// {
// 	t_vec3	resultante;

// 	resultante.x = u.x + v.x + w.x;
// 	resultante.y = u.y + v.y + w.y;
// 	resultante.z = u.z + v.z + w.z;
// 	return (resultante);
// }

t_ray		create_ray(t_vec3 origin, t_vec3 direction)
{
	t_ray result;

	result.origin = origin;
	result.direction = direction;
	return (result);
}


/*
gmzorz version 
t_bool	camera_ray_init(t_scene *scene, t_ray *ray, t_real u, t_real v)
{ 
	//equivalent a get_direction()
	worldspace;
	worldspace.x = (2 * ((u + 0.5) / scene->mlx.width) - 1)
		* scene->camera->view_range * scene->ratio;
	worldspace.y = (1 - 2 * ((v + 0.5) / scene->mlx.height))
		* scene->camera->view_range;
	worldspace.z = 1;
	// IL SET ICI le RAY ORIGIN ET DIRECTION ALORS QUE MOI JE LE FAIS DANS RAY TRACING ligne 162
	// == ligne 175 dir = multiply_by_matrix(dir, scene-cam-matrix)
	ray->origin = mat4_get(scene->camera->world, m_origin);
	ray->dir = vec3_unit(mat4_mult_dir(scene->camera->world,
				worldspace));
	ray->max = M_INFINITY;
	return (true);
}
*/

t_vec3		get_direction(t_scene *scene, int x, int y)
{
	double fov_coeff;
	double aspect_ratio;
	double p_x;
	double p_y;

	// fov_coeff = scene->cam->view_range;
	fov_coeff = tanf((double)scene->cam->fov / 2 * M_PI / 180);
	aspect_ratio = (double)get_mlx()->width / (double)get_mlx()->height;
	p_x = (2 * (x + 0.5) / (double)get_mlx()->width - 1) * aspect_ratio * fov_coeff;
	p_y = (1 - 2 * (y + 0.5) / (double)get_mlx()->height) * fov_coeff;

	// jai mis -p_x
	return (new_vector(-p_x, p_y, 1));
}

t_ray	ray_to_pixel(t_scene *scene, int x, int y)
{
	t_ray ray;
		// rempli ici la matrice m.
		// scene->cam->m = look_at(scene->cam->origin, scene->cam->dir);
		// t_vec3 ori = multiply_by_matrix(new_vector(0, 0, 0), scene->cam->m);
		t_vec3 dir = get_direction(scene, x, y);

		dir = multiply_by_matrix(dir, scene->cam->m);
		dir = vec_sub(dir, scene->cam->origin);
		dir = vec_normalize(dir);
		ray = create_ray(scene->cam->origin, dir);
	return(ray);
}

void	ray_tracing(t_scene *scene)
{
	t_mlx *mlx = get_mlx();
	int x = 0;
	int y = 0;
	int color;
	t_ray ray;

	scene->cam->m = look_at(scene->cam->origin, scene->cam->dir);
	while (y < mlx->height)
	{
		x = 0;
		while (x < mlx->width)
		{
			// ray_to_pixel renvoie un ray origin xyz, et direction normalisé
			ray = ray_to_pixel(scene, x, y);
			// ray.direction = new_vector(ray.direction.x, ray.direction.y, ray.direction.z);
			// ray.direction = rotate_dir(ray.direction, scene);
			color = get_hit_color(scene, ray);
			my_mlx_pixel_put(mlx, x, y, color);
			x++;
		}
		y++;
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
}

void	make_scene(t_scene *scene)
{
	t_mlx *mlx;

	mlx = get_mlx();
	//
	scene->cam->view_range = tan((scene->cam->fov * 0.5) * (M_PI / 180));
	// scene->cam->m = look_at(scene->cam->origin, scene->cam->dir);
	//
	ray_tracing(scene);
	//
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