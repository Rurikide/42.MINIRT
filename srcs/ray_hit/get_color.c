#include "../../incls/mini_rt.h"

//fonction pour gérer les ombres
double	shadow_ray(t_vec3 hit_point, t_scene *scene)
{
	size_t i;
	t_vec3 dir_lit;
	double distance;
	t_shape *obj;

	dir_lit = vec_normalize(vec_sub(scene->lit->origin, hit_point)); //vecteur qui part de la source de lumiere au hit_point
	i = 0;
	while (i < scene->objs->total)
	{
		obj = (t_shape *)scene->objs->elements[i];
		distance = obj->hit_obj(obj->shape, hit_point, dir_lit);
		/*si la distance est > 0 et distance < à la distance entre mon hit_point et la lumière */
		if (distance > 0 && distance < vec_len(vec_sub(scene->lit->origin, hit_point))
			&& scene->objs->elements[i] != i) 
			return (-1); // je suis dans le spot_light
		i++;
	}
	return (0);
}

double	spec_light(t_vec3 norm, t_vec3 dir, t_vec3 hit_point, t_scene *scene)
{
	t_vec3 reflet;
	t_vec3 spot;

	spot = vec_normalize(vec_sub(scene->lit->origin, hit_point));
	reflet = vec_normalize(vec_sub(dir, vec_multiply(norm, 2 * vec_dot(norm, dir))));
	return (pow(fmax(vec_dot(reflet, spot), 0), 32) * scene->lit->ratio);
}

/*Calcul l'angle formé par le vecteur du spot_light et le vecteur du hit_point
Spot_light se situe entre -1 et 1, sachant que 0 est l'angle qui donne la lumière
la plus intense car directement face au point d'intersection*/
double	spot_light(t_vec3 hit_point, t_scene *scene, t_vec3 norm)
{
	t_vec3	spot;
	double	spot_light;

	spot = vec_normalize(vec_sub(scene->lit->origin, hit_point));
	spot_light = vec_dot(norm, spot) * scene->lit->ratio; 
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
	if (shadow == 0) // je suis pas dans le spotlight
		color = add_3_colors(multiply_color(rgb_to_int((((t_sp *)obj->shape)->color)), scene->amb->ratio), 
		multiply_color(rgb_to_int((((t_sp *)obj->shape)->color)), spot_light(hit_point, scene, norm)), 
		multiply_color(rgb_to_int((((t_sp *)obj->shape)->color)), spec_light(norm, direction, hit_point, scene))); 
	else // je suis dans la lumière
		color = add_color(
			add_3_colors((multiply_color(rgb_to_int((((t_sp *)obj->shape)->color)), scene->amb->ratio)), 
			multiply_color(rgb_to_int((((t_sp *)obj->shape)->color)), spot_light(hit_point, scene, norm)), 0)
			,-30);
	return (color);
}