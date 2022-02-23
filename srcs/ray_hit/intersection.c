#include "../../incls/mini_rt.h"

/*fonction qui regarde si le rayon hit un obj de la scene*/
// int	hit_obj(t_scene *scene, t_ray *ray)
// {
// 	if (type == sphere)
// 		int intersect_sphere(scene, ray);
// }

/*fonction avec 2 boucles while imbriqué*/


double	 find_dist(t_sphere *sphere, t_vec3 cam, t_vec3 direction)
{
	double	distance;

	distance = 0;
	if (sphere->type == SPHERE)
		distance = hit_sphere(cam, direction, sphere);
	// else if (type == CYL)
	// 	distance = 
	// else 
	// 	distance = 
	return (distance);

}

/*fonction qui renvoi la couleur frappée par le rayon
on ne garde que la couleur de l'objet le plus proche de la cam*/
int	intersection(t_scene *scene, t_vec3 direction)
{
	int	i;
	double distance;
	double closer;
	int		color;	

	closer = 10000;
	color = 0xFFFFFF;
	i = 0;
	while (i < scene->nb_obj)
	{
		distance = find_dist(scene->sp, scene->cam->origin, direction);
		if (distance > 0 && distance < closer)
		{
			closer = distance;
			color = get_color(scene->sp, direction, scene, distance);
		}
		i++;
	}
	return (color);
}

double	shadowing(t_vec3 hit_point, t_scene *scene)
{
	int i;
	t_vec3 dir;
	double dist;

	dir = vec_normalize(vec_sub(scene->light->origin, hit_point));
	i = 0;
	while (i < scene->nb_obj)
	{
		dist = find_dist(scene->sp, hit_point, dir);
		if (dist > 0 && dist < vec_len(vec_sub(hit_point, scene->light->origin)))
			return (-1);
		i++;
	}
	return (0);
}

int	get_color(t_sphere *sphere, t_vec3 direction, t_scene *scene, double distance)
{
	t_vec3	hit_point;
	t_vec3 norm;
	int	color;
	double shadow;

	hit_point = get_hit_point_sp(scene, direction, distance);
	if (sphere->type == SPHERE)
		norm = vec_normalize(vec_sub(hit_point, sphere->center));
	shadow = shadowing(hit_point, scene);
	if (shadow == 0)
		color = 0x0000FF;
	else
		color = rgb_to_int(sphere->color);
	return (color);
}