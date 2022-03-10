#include "../../incls/mini_rt.h"

double hit_plane(void *plan, t_vec3 ray_origin, t_vec3 ray_direction)
{
	t_pl	*pl;
	double	lo_po;
	double	ldotn;
	double	t;
	double	d;
	
	pl = (t_pl *)plan;
	lo_po = (vec_dot(vec_sub(pl->origin, ray_origin), vec_normalize(pl->dir)));
	ldotn = vec_dot(ray_direction, vec_normalize(pl->dir));
	t = lo_po / ldotn;
	if ( t == 0.0)
		t = M_EPSILON;
	return (t);

}

double	hit_cylinder(void *cylinder, t_vec3 ray_origin, t_vec3 ray_direction)
{
	t_cy	*cyl;
	double	a;
	double	b;
	double	c;
	double	disc;
	double	t1;
	double	t2;
	double	t;
	double	min;
	double	max;

	cyl = (t_cy *)cyl;
	a = ray_direction.x * ray_direction.x + ray_direction.z * ray_direction.z;
	b = 2 * ray_origin.x * ray_direction.x + 2 * ray_origin.z * ray_direction.z;
	c = ray_origin.x * ray_origin.x + ray_origin.z * ray_origin.z - 1;
	disc = b * b - 4 * a  *c;
	t1 = (- b - sqrtf(disc)) / (2 * a);
	t2 = (- b + sqrtf(disc)) / (2 * a);
	min = fmin(t1, t2);
	max = fmax(t1, t2);
	if (min >= 0)
		t = min;
	else
		t = max;
	return (t);
	
}