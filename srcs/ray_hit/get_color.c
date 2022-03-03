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
		/*si la distance est > 0 c'est que ca hit devant la cam
		mais si elle est inférieure à la len du vecteur, c'est qu'on intercepte un autre
		objet en chemin donc il va y avoir une ombre sur l'objet*/
		if (distance > 0 && distance < vec_len(vec_sub(scene->lit->origin, hit_point))
			&& scene->objs->elements[i - 1] != i) 
			return (-1); //je suis dans le spot_light
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

t_rgb	get_ambient_lit(t_scene *scene)
{
	t_rgb	color;

	color.r = scene->amb->ratio * scene->amb->color.r / 255;
	color.g = scene->amb->ratio * scene->amb->color.g / 255;
	color.b = scene->amb->ratio * scene->amb->color.b / 255;
	return (color);
}

t_rgb	multiply_rgb(t_rgb c1, t_rgb c2)
{
	t_rgb color;

	color.r = (((c1.r / 255) * (c2.r / 255)) * 255);
	color.g = (((c1.g / 255) * (c2.g / 255)) * 255);
	color.b = (((c1.b / 255) * (c2.b / 255)) * 255);

	return (color);
}

int	get_color(t_shape *obj, t_vec3 direction, t_scene *scene, double distance)
{
	t_vec3	hit_point;
	t_vec3 norm;
	int	color;
	int	i;
	double shadow;
	t_rgb ambiant_light;

	i = 0;
	hit_point = get_hit_point_sp(scene, direction, distance);
	if (obj->type == 1)
		norm = vec_normalize(vec_sub(hit_point, ((t_sp *)obj->shape)->origin));
	ambiant_light = get_ambient_lit(scene);
	//printf("%f\n", ambiant_light);
	shadow = shadow_ray(hit_point, scene); 
	 if (shadow == 0) //il n'y a rien qui interfère entremon objet et la lumière, donc je dois afficher la couleu de l'objet en tenant compte des lumières
	 {
		color = rgb_to_int(multiply_rgb(ambiant_light, (((t_sp *)obj->shape)->color)));


	 } 
	// 	color = add_3_colors(multiply_color(rgb_to_int((((t_sp *)obj->shape)->color)), scene->amb->ratio), 
	// 	multiply_color(rgb_to_int((((t_sp *)obj->shape)->color)), spot_light(hit_point, scene, norm)), 
	// 	multiply_color(rgb_to_int((((t_sp *)obj->shape)->color)), spec_light(norm, direction, hit_point, scene))); 
	// else //il y a un objet entre ma lumière et mon objet, je dois afficher de l'ombre sur ledit objet
	// {	
	// 	add_color( 
	// 		add_3_colors((multiply_color(rgb_to_int((((t_sp *)obj->shape)->color)), scene->amb->ratio)), 
	// 		multiply_color(rgb_to_int((((t_sp *)obj->shape)->color)), spot_light(hit_point, scene, norm)), 0)
	// 		,-30);
		//printf("test");
	//}
	return (color);
}