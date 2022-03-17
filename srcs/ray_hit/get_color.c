#include "../../incls/mini_rt.h"

/*si la distance est > 0 c'est que ca hit devant la cam mais 
si elle est inférieure à la len du vecteur, c'est qu'on intercepte
un autre objet en chemin donc il va y avoir une ombre sur l'objet*/
double	shadow_ray(t_vec3 hit_point, t_scene *scene, t_vec3 ray_dir)
{
	size_t i;
	t_vec3 dir_lit;
	double distance;
	t_shape *obj;

	dir_lit = vec_normalize(vec_sub(scene->lit->origin, hit_point));
	i = 0;
	while (i < scene->objs->total)
	{
		obj = (t_shape *)scene->objs->elements[i];
		distance = obj->hit_obj(obj->shape, hit_point,dir_lit);
		if (distance > 0 && distance < vec_len(vec_sub(scene->lit->origin, hit_point))
			&& scene->objs->elements[i - 1] != i) 
			return (-1);
		i++;
	}
	return (0);
}

/*R=2(N⋅L)N−L*/
t_vec3 get_reflect(t_vec3 norm, t_vec3 ray_dir)
{
	t_vec3 reflect;

	reflect = vec_sub(ray_dir, vec_multiply(norm, 2 * vec_dot(ray_dir, norm)));
	return (vec_normalize(reflect));
}

/*Specular = (V.R)ˆn
V = view_direction ou ray_direction
R = Reflect_direction
n = specular exponent*/
double	spec_light(t_vec3 norm, t_vec3 ray_dir, t_vec3 hit_point, t_scene *scene)
{
	t_vec3 reflect;
	t_vec3 view_dir;
	double n;
	double specular;

	n = 45;
	reflect = get_reflect(norm, ray_dir);
	view_dir = vec_normalize(vec_sub(scene->lit->origin, hit_point));
	specular = vec_dot(reflect, view_dir);
	return (pow(fmax(specular, 0.0), n) * scene->lit->ratio * 1.2);
}

/*Lambert's Cosine Law :
Calcul l'angle formé par le vecteur du spot_light et le vecteur du hit_point
Spot_light se situe entre -1 et 1, sachant que 0 est l'angle qui donne la lumière
la plus intense car directement face au point d'intersection*/
double	spot_light(t_vec3 hit_point, t_scene *scene, t_vec3 norm)
{
	t_vec3	spot;
	t_vec3	lit_dir;
	double	spot_light;

	lit_dir = vec_normalize(vec_sub(scene->lit->origin, hit_point));
	spot_light = vec_dot(norm, lit_dir); 
	spot_light *= scene->lit->ratio;
	if (spot_light < 0.0) // if < 0 that would mean the light is behind the normal surface, so ne devrait pas éclairer
		spot_light = 0.0;
	return (spot_light);
}

/*Shading at P = diffuse * kd + specular * ks*/
int	get_color(t_shape *obj, t_ray ray, t_scene *scene, double distance)
{
	int color;
	t_vec3	hit_p;
	t_vec3	norm;
	t_ray	lit_ray;
	t_mix_lit	mix;

	hit_p = get_hit_point(scene, ray, distance);
	if (obj->type == 1)
		norm = vec_normalize(vec_sub(hit_p, obj->origin));
	if (obj->type == 2)
		norm = get_cyl_norm(hit_p, obj);
	if (obj->type == 3)
		norm = vec_normalize(obj->dir);
	lit_ray.origin = scene->lit->origin;
	lit_ray.direction = vec_normalize(vec_sub(lit_ray.origin, hit_p));
	
	//ambient light
	mix.ambient_lit = rgb_to_int(get_ambient_lit(scene, obj->color));

	//diffuse light
	mix.kd = spot_light(hit_p, scene, norm);
	mix.diffuse_lit = multiply_color(rgb_to_int(get_diffuse_lit(obj->color, scene)), mix.kd * 2);

	//specular light
	mix.spec_lit = multiply_color(rgb_to_int(obj->color), spec_light(norm, ray.direction, hit_p, scene));

	mix.shadow = shadow_ray(vec_add(hit_p, lit_ray.direction), scene, lit_ray.direction);
	if (mix.shadow == 0)
		color = add_3_colors(mix.ambient_lit, mix.diffuse_lit, mix.spec_lit);
	else 
		color = add_2_colors(mix.ambient_lit, rgb_to_int(new_color(0,0,0)));
	return (color);
}