#include "../../incls/mini_rt.h"

t_sphere	*init_sphere()
{
	t_sphere *sphere;

	sphere = ft_calloc(1, sizeof(t_sphere));
	sphere->color = new_color(100, 0, 255);
	sphere->center = new_vector(500, 0, 0);
	sphere->rad = 30;
	sphere->type = SPHERE;

	return (sphere);
}

t_cam	*init_cam()
{
	t_cam *cam;

	cam = ft_calloc(1, sizeof(t_cam));
	cam->dir = new_vector(1, 0, 0);
	cam->origin = new_vector(-200, 0, 0);
	cam->fov = 70;

	return (cam);
}

t_scene *init_scene()
{
	t_scene *scene;
	
	scene = ft_calloc(1, sizeof(t_scene));
	scene->sp = init_sphere();
	scene->cam = init_cam();
	scene->nb_obj = 1;
	return (scene);
}

t_vec3	get_norm_sphere(t_scene *scene, t_vec3	hit_p)
{
	t_vec3 normal;

	normal = vec_sub(hit_p, scene->sp->center);
	return (vec_normalize(normal));
}

t_vec3	get_hit_point_sp(t_scene *scene, t_vec3 direction, double distance)
{
	t_vec3	hit_p;

	hit_p = vec_add(vec_multiply(direction, distance), scene->cam->origin);
	return (hit_p);
}

double	get_root(double disc, double b)
{
	double	t1;
	double	t2;
	double	t;
	double	min;
	double	max;
	
	t1 = -b + sqrt(disc);
	t2 = -b - sqrt(disc);
	min = fmin(t1, t2);
	max = fmax(t1, t2);
	if (min >= 0)
		t = min;
	else
		t = max;
	return (t);
}

double hit_sphere(t_vec3 cam, t_vec3 direction, t_sphere *sphere)
{
	double	a;
	double	b;
	double	c;
	double	disc;
	t_vec3	v;

	v = vec_sub(cam, sphere->center);
	a = vec_dot(direction, direction);
	b = vec_dot(direction, v);
	c = vec_dot(v, v) - sphere->rad * sphere->rad;
	disc = b * b - c;
	if (disc >= 0)
		return (get_root(disc, b));
	else
		return (0);
}