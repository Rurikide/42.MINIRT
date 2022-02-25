#include "../../incls/mini_rt.h"

//fonction pour gérer les ombres
double	shadow_ray(t_vec3 hit_point, t_scene *scene)
{
	int i;
	t_vec3 dir;
	double distance;
	t_shape *obj;

	dir = vec_normalize(vec_sub(scene->lit->origin, hit_point)); // la direction est changée à chaque fois que le hit_point change
	i = 0;
	while (i < scene->objs->total)
	{
		obj = (t_shape *)scene->objs->elements[i];
		distance = obj->hit_obj(obj->shape, hit_point, dir);
		/*si la distance est > 0 et distance < à la distance entre mon hit_point et la lumière */
		if (distance > 0 && distance < vec_len(vec_sub(scene->lit->origin, hit_point))) 
			return (-1); // je suis dans le spot_light
		i++;
	}
	return (0);
}

// fonction pour récupérer la bonne couleur

double	spot_light(t_vec3 hit_point, t_scene *scene, t_vec3 norm)
{
	t_vec3	spot;
	double	spot_light;

	spot = vec_normalize(vec_sub(scene->lit->origin, hit_point)); // on calcule la direction entre la lumiere et le point d'intersection
	spot_light = vec_dot(norm, spot) * scene->lit->ratio; // plus on est proche de 0, plus la lumiere est intense
	return (spot_light);
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
		norm = vec_normalize(vec_sub(hit_point, ((t_sp *)obj->shape)->origin));
	shadow = shadow_ray(hit_point, scene); // j'envoie un rayon depuis le point d'origine de la lumière
	if (shadow == -1) // je suis pas dans le spotlight
		color = multiply_color(rgb_to_int((((t_sp *)obj->shape)->color)), scene->amb->ratio) + multiply_color(rgb_to_int((((t_sp *)obj->shape)->color)), spot_light(hit_point, scene, norm)); // il me faut un mix de la couleur de la sphere, du spotlight et de la lumiere ambiante
	// else if (obj->type == 2)
	// {

	// }
	//shadow = shadowing(hit_point, scene);
	else // je suis dans la lumière
		color = rgb_to_int(color_multiply_rgb((((t_sp *)obj->shape)->color),(scene->amb->color),scene->amb->ratio)); //lumiere ambiante
	return (color);
}