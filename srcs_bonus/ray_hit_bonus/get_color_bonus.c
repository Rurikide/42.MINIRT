/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadia <jbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 14:20:26 by jbadia            #+#    #+#             */
/*   Updated: 2022/03/25 11:11:46 by jbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incls/mini_rt.h"

/*si la distance est > 0 c'est que ca hit devant la cam mais 
si elle est inférieure à la len du vecteur, c'est qu'on intercepte
un autre objet en chemin donc il va y avoir une ombre sur l'objet*/
double	shadow_ray(t_vec3 hit_point, t_scene *scene)
{
	size_t	i;
	t_vec3	dir_lit;
	double	distance;
	t_shape	*obj;
	double	len;

	dir_lit = vec_normalize(vec_sub(scene->lit->origin, hit_point));
	len = vec_len(vec_sub(scene->lit->origin, hit_point));
	i = 0;
	while (i < scene->objs->total)
	{
		obj = (t_shape *)scene->objs->elements[i];
		distance = obj->hit_obj(obj->shape, hit_point, dir_lit);
		if ((distance > -0.99 && distance < len)
			|| fabs(distance - len) < 0.001)
			return (-1);
		i++;
	}
	return (0);
}

/*R=2(N⋅L)N−L*/
t_vec3	get_reflect(t_vec3 norm, t_vec3 ray_dir)
{
	t_vec3	reflect;

	reflect = vec_sub(ray_dir, vec_multiply(norm, 2 * vec_dot(ray_dir, norm)));
	return (vec_normalize(reflect));
}

/*Specular = (V.R)ˆn
V = view_direction ou ray_direction
R = Reflect_direction
n = specular exponent*/
double	spec_light(t_vec3 norm, t_vec3 ray_dir, t_vec3 hit_p, t_scene *scene)
{
	t_vec3	reflect;
	t_vec3	view_dir;
	double	n;
	double	specular;

	n = 25;
	reflect = get_reflect(norm, ray_dir);
	view_dir = vec_normalize(vec_sub(scene->lit->origin, hit_p));
	specular = vec_dot(reflect, view_dir);
	return (pow(fmax(specular, 0.0), n) * scene->lit->ratio);
}

/*Lambert's Cosine Law :
Calcul l'angle formé par le vecteur du spot_light et le vecteur du hit_point
Spot_light se situe entre -1 et 1, sachant que 0 est l'angle qui donne la lumière
la plus intense car directement face au point d'intersection - Si le spotlight
est inférieur à 0, that would mean the light is behind the normal surface,
so ne devrait pas éclairer*/
double	spot_light(t_vec3 hit_point, t_scene *scene, t_vec3 norm)
{
	t_vec3	lit_dir;
	double	spot_light;

	lit_dir = vec_normalize(vec_sub(scene->lit->origin, hit_point));
	spot_light = vec_dot(norm, lit_dir);
	spot_light *= scene->lit->ratio;
	if (spot_light < 0.0)
		spot_light = 0.0;
	return (spot_light);
}

/*Shading at P = diffuse * kd + specular * ks*/
int	get_color(t_shape *obj, t_ray ray, t_scene *scene, double distance)
{
	int			color;
	t_vec3		hit_p;
	t_vec3		norm;
	t_ray		lit_ray;
	t_mix_lit	mix;

	hit_p = vec_add(vec_multiply(ray.direction, distance), ray.origin);
	if (obj->type == 1)
		norm = vec_normalize(vec_sub(hit_p, obj->origin));
	if (obj->type == 2)
		norm = get_cyl_norm(hit_p, (t_cy *)obj->shape);
	if (obj->type == 3)
		norm = vec_normalize(obj->dir);
	lit_ray.direction = vec_normalize(vec_sub(scene->lit->origin, hit_p));
	mix.ambient_lit = rgb_to_int(get_ambient_lit(scene, obj->color));
	mix.kd = spot_light(hit_p, scene, norm);
	mix.diffuse_lit = multiply_color(rgb_to_int
			(get_diffuse_lit(obj->color, scene)), mix.kd * 1.5);
	mix.spec_lit = multiply_color(rgb_to_int(obj->color),
			spec_light(norm, ray.direction, hit_p, scene));
	if (shadow_ray(vec_add(hit_p, lit_ray.direction), scene) == 0)
		color = add_3_colors(mix.ambient_lit, mix.diffuse_lit, mix.spec_lit);
	else
		color = add_2_colors(mix.ambient_lit, rgb_to_int(new_color(0, 0, 0)));
	return (color);
}
