#include "../../incls/mini_rt.h"

double	check_cyl_root(t_vec3 ray_origin, t_vec3 ray_direction, t_shape *cyl, double disc, double b);


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

t_vec3	get_cyl_norm(t_vec3 hit_p, t_shape *cyl)
{
	double	d;
	t_vec3	norm;
	t_vec3	sum;

	d = vec_dot(vec_sub(hit_p, cyl->origin), cyl->dir);
	sum = vec_add(cyl->origin, vec_multiply(cyl->origin, d));
	norm = vec_normalize(vec_sub(hit_p, sum));

	return (norm);
}

double	calc_t(float caoc, float card, float caca, float y)
{
	float	t;

	if (y < 0)
		t = (0 - caoc) / card;
	else
		t = (caca - caoc) / card;
	return (t);
}

double	hit_cylinder(void *cylinder, t_vec3 ray_origin, t_vec3 ray_direction)
{
	t_cy	*cyl;
	t_vec3	a_sqrt;
	t_vec3	right;
	double	a;
	double	b;
	double	c;
	double	disc;

	cyl = (t_cy *)cylinder;
	double height = 10;
	double diameter = 50;
	double y;
	
	// a_sqrt = vec_sub(ray_direction, vec_multiply(cyl->dir, vec_dot(ray_direction, cyl->dir)));

	// a = vec_dot(a_sqrt, a_sqrt);
	// right = vec_sub( vec_sub (ray_origin, cyl->origin), vec_multiply(cyl->dir, vec_dot(vec_sub(ray_origin, cyl->origin), cyl->dir)));
	// b = 2 * vec_dot(a_sqrt, right);
	// c = vec_dot(right, right) - (cyl->rad * cyl->rad);
	// disc = b * b - 4 * a  *c;
	// if (disc >= 0)
	// 	return (get_root(sqrtf(disc), b));
	// else
	// 	return (0);

	t_vec3	top;

	top = vec_sub(vec_add(cyl->origin, vec_multiply(cyl->dir, height)), cyl->origin);
	a = vec_dot(top, top) - vec_dot(top, ray_direction) * vec_dot(top, ray_direction);
	b = vec_dot(top, top) * vec_dot(vec_sub(ray_origin, cyl->origin), ray_direction) - vec_dot(top, vec_sub(ray_origin, cyl->origin)) * vec_dot(top, ray_direction);
	c = vec_dot(top, top) * vec_dot(vec_sub(ray_origin, cyl->origin), vec_sub(ray_origin, cyl->origin)) - 
		vec_dot(top, vec_sub(ray_origin, cyl->origin)) * vec_dot(top, vec_sub(ray_origin, cyl->origin)) - (diameter / 2) * (diameter / 2)
		* vec_dot(top, top);
	disc = (b * b - a * c);
	if (disc < 0)
		return (0);
	y = vec_dot(top, vec_sub(ray_origin, cyl->origin)) + ((-b - sqrt((b * b - a * c))) / a) * vec_dot(top, ray_direction);
	if (y > 0 && y < 1)
		return (((-b - sqrt((b * b - a * c))) / a));
	y = calc_t(vec_dot(top, vec_sub(ray_origin, cyl->origin)), vec_dot(top, ray_direction), vec_dot(top, top), y);
	if (fabs(b + a * y) < sqrt((b * b - a * c)))
		return (y);
	return (0);
}

// double	check_cyl_root(t_vec3 ray_origin, t_vec3 ray_direction, t_shape *cyl, double disc, double b)
// {
// 	double	t1;
//   	double	t2;
//   	double	t;
//   	double	min;
//   	double	max;
// 	t_vec3 q;
// 	t_vec3	top_cyl;
// 	double height = 5;
	
// 	top_cyl = vec_add(cyl->origin, vec_multiply(cyl->origin, height));
// 	t1 = (-b + disc) / 2;
// 	if (t1 > 0)
// 	{
// 		q = vec_add(ray_origin, vec_multiply(ray_direction, t1));
// 		if (vec_dot(cyl->dir, vec_sub(q, cyl->origin)) <= 0)
// 			t1 = -1;
// 		if (vec_dot(cyl->dir, vec_sub(q, top_cyl)) >= 0)
// 			t1 = -1;
// 	}
// 	t2 = (-b - disc) / 2;
// 	if (t2 > 0)
// 	{
// 		q = vec_add(ray_origin, vec_multiply(ray_direction, t2));
// 		if (vec_dot(cyl->dir, vec_sub(q, cyl->origin)) <= 0)
// 			t2 = -1;
// 		if (vec_dot(cyl->dir, vec_sub(q, top_cyl)) >= 0)
// 			t2 = -1;
// 	}
// 	if (t1 < 0 && t2 < 0)
// 		return (0.0);
// 	min = fmin(t1, t2);
// 	max = fmax(t1, t2);
// 	if (min >= 0)
// 		t = min;
// 	else
// 		t = max;
// 	return (t);
// }