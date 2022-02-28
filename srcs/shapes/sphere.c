#include "../../incls/mini_rt.h"

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
	

	t1 = -b + sqrt(disc)/2;
	t2 = -b - sqrt(disc)/2;
	min = fmin(t1, t2);
	max = fmax(t1, t2);
	if (min >= 0)
		t = min;
	else
		t = max;
	return (t);
}

double hit_sphere(void *sphere, t_vec3 cam, t_vec3 direction)
{
	double	b;
	double	c;
	double	disc;
	t_vec3	v;
	t_sp *sp;

	sp = (t_sp *)sphere;
	v = vec_sub(cam, sp->origin);
	b = 2 * vec_dot(direction, v);
	c = vec_dot(v, v) - sp->rad * sp->rad;
	disc = b * b - 4*c;
	if (disc >= 0)
		return (get_root(disc, b));
	else
		return (0);
}
