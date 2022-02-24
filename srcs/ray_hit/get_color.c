#include "../../incls/mini_rt.h"

//fonction pour gérer les ombres
// double	shadowing(t_vec3 hit_point, t_scene *scene)
// {
// 	int i;
// 	t_vec3 dir;
// 	double dist;

// 	dir = vec_normalize(vec_sub(scene->light->origin, hit_point));
// 	i = 0;
// 	while (i < scene->nb_obj)
// 	{
// 		dist = find_dist(scene->sp, hit_point, dir);
// 		if (dist > 0 && dist < vec_len(vec_sub(hit_point, scene->light->origin)))
// 			return (-1);
// 		i++;
// 	}
// 	return (0);
// }

// fonction pour récupérer la bonne couleur

double	spot_light(t_vec3 hit_point, t_scene *scene, t_vec3 norm)
{
	double	spot;

	spot = 100 * scene->lit->ratio * vec_dot(vec_sub(scene->lit->origin, hit_point), norm) / vec_squared(vec_sub(scene->lit->origin, hit_point));
	return(spot);
}

int	get_color(t_shape *obj, t_vec3 direction, t_scene *scene, double distance)
{
	t_vec3	hit_point;
	t_vec3 norm;
	int	color;
	int	i;
	double shadow;
	double	test;

	i = 0;
	hit_point = get_hit_point_sp(scene, direction, distance);
	if (obj->type == 1)
	{
		norm = vec_normalize(vec_sub(hit_point, ((t_sp *)obj->shape)->origin));
		color = rgb_to_int(color_multiply_rgb((((t_sp *)obj->shape)->color),(scene->amb->color),scene->amb->ratio));
		
	}
	// else if (obj->type == 2)
	// {

	// }
	//shadow = shadowing(hit_point, scene);
	// if (shadow == 0)
	// 	color = 0x0000FF;
	return (color);
}