#include "../../incls/mini_rt.h"


t_rgb	multiply_rgb_rgb(t_rgb c1, t_rgb c2)
{
	t_rgb color;

	color.r = (c1.r * c2.r) / 255;
	color.g = (c1.g * c2.g) / 255;
	color.b = (c1.b * c2.b) / 255;

	return (color);
}

t_rgb	multiply_rgb_double(t_rgb c, double d)
{
	t_rgb color;

	color.r = (c.r * d);
	if (c.r > 255)
		c.r = 255;
	color.g = (c.g * d);
	if (c.g > 255)
		c.g = 255;
	color.b = (c.b * d);
	if (c.b > 255)
		c.b = 255;

	return (color);
}

t_rgb	add_rgb_double(t_rgb c1, double d)
{
	t_rgb color;

	color.r = (c1.r + d);
		if (color.r > 255)
		color.r = 255;
	color.g = (c1.g + d);
	if (color.g > 255)
		color.g = 255;
	color.b = (c1.b + d);
	if (color.b > 255)
		color.b = 255;

	return (color);
}

t_rgb	add_rgb(t_rgb c1,t_rgb c2)
{
	t_rgb color;

	color.r = (c1.r + c2.r);
		if (color.r > 255)
		color.r = 255;
	color.g = (c1.g + c2.g);
	if (color.g > 255)
		color.g = 255;
	color.b = (c1.b + c2.b);
	if (color.b > 255)
		color.b = 255;

	return (color);
}

t_rgb	get_obj_color(t_shape* obj)
{
	void *elem;

	elem = obj;
	if (obj->type == 1)
	{
		//printf("R = %d \n", ((t_sp *)elem)->color.r);
		return (((t_sp *)elem)->color);
	}
	else	
		return (new_color(0,0,0));
}

t_rgb	get_diffuse_lit(t_rgb obj, t_scene *scene)
{
	t_rgb	color;

	color.r = (scene->lit->ratio * 255 * obj.r) / 255;
	color.g = (scene->lit->ratio * 255 * obj.g) / 255;
	color.b = (scene->lit->ratio * 255 * obj.b) / 255;
	return (color);
}

t_rgb	get_spec_lit(t_rgb obj,	double ks)
{
	t_rgb	color;

	color.r = (ks * 255 * obj.r) / 255;
	color.g = (ks * 255 * obj.g) / 255;
	color.b = (ks * 255 * obj.b) / 255;
	return (color);
}

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

t_rgb	get_ambient_lit(t_scene *scene, t_rgb obj)
{
	t_rgb	color;

	color.r = (scene->amb->ratio * scene->amb->color.r * obj.r) / 255;
	color.g = (scene->amb->ratio * scene->amb->color.g * obj.g) / 255;
	color.b = (scene->amb->ratio * scene->amb->color.b * obj.b) / 255;
	return (color);
}

/*Shading at P = diffuse * kd + specular * ks*/
int	get_color(t_shape *obj, t_ray ray, t_scene *scene, double distance)
{
	int color;
	double shadow;
	double	kd;
	t_vec3	hit_p;
	t_vec3	norm;
	t_ray	lit_ray;
	int	ambient_lit;
	int	diffuse_lit;
	int	spec_lit;

	hit_p = get_hit_point_sp(scene, ray, distance);
	norm = vec_normalize(vec_sub(hit_p, ((t_sp *)obj->shape)->origin));
	lit_ray.origin = scene->lit->origin;
	lit_ray.direction = vec_normalize(vec_sub(lit_ray.origin, hit_p));
	
	//ambient light
	ambient_lit = rgb_to_int(get_ambient_lit(scene, ((t_sp *)obj->shape)->color));

	//diffuse light
	kd = spot_light(hit_p, scene, norm);
	diffuse_lit = multiply_color(rgb_to_int(get_diffuse_lit((((t_sp *)obj->shape)->color), scene)), kd * 2);

	//specular light
	spec_lit = multiply_color(rgb_to_int((((t_sp *)obj->shape)->color)), spec_light(norm, ray.direction, hit_p, scene));

	shadow = shadow_ray(vec_add(hit_p, lit_ray.direction), scene, lit_ray.direction);
	if (shadow == 0)
		color = add_3_colors(ambient_lit, diffuse_lit, spec_lit);
	else 
		color = add_2_colors(ambient_lit, rgb_to_int(new_color(0,0,0)));
		//add_2_colors(ambient_lit, multiply_color(diffuse_lit, -0.1)); // ou on ajoute du noir et l'ambiant light seulement ... ?
	return (color);
}