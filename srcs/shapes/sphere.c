#include "../../incls/mini_rt.h"

t_vec3	get_hit_point_sp(t_scene *scene, t_ray ray, double distance)
{
	t_vec3	hit_p;

	hit_p = vec_add(vec_multiply(ray.direction, distance), ray.origin);
	// 	printf("__________________________\n");
	// printf("ray_p.x = %f\n", ray.origin.x);
	// printf("ray_p.y = %f\n", ray.origin.y);
	// printf("ray_p.z = %f\n", ray.origin.z);
	
	return (hit_p);
}

double	get_root(double disc, double b)
{
  double	t1;
  double	t2;
  double	t;
  double	min;
  double	max;
	

	t1 = (-b + disc) / 2;
	t2 = (-b - disc) / 2;
	min = fmin(t1, t2);
	max = fmax(t1, t2);
	if (min >= 0)
		t = min;
	else
		t = max;
	return (t);
}

double hit_sphere(void *sphere, t_vec3 ray_origin, t_vec3 ray_direction)
{
	double	b;
	double	c;
	double	disc;
	t_vec3	v;
	t_sp *sp;

	sp = (t_sp *)sphere;
	v = vec_sub(ray_origin, sp->origin);
	b = 2 * vec_dot(ray_direction, v);
	c = vec_dot(v, v) - sp->rad * sp->rad;
	disc = b * b - 4*c;
	if (disc >= 0)
		return (get_root(sqrt(disc), b));
	else
		return (0);
}
