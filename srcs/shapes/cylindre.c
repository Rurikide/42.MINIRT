// #include "../../incls/mini_rt.h"

// t_vec3 get_cyl_norm(t_vec3 hit_p, t_cy *cyl)
// {
// 	t_vec3	v;
// 	t_vec3 norm;

// 	v = vec_sub(hit_p, cyl->origin);
// 	norm = vec_sub(v, vec_multiply(cyl->dir, vec_dot(cyl->dir, v)));
// 	return (vec_normalize(norm));
// }

// bool	quad_cyl(t_quadra param, double *t0, double *t1)
// {
// 	double q;

// 	if (param.disc < 0)
// 		return (false);
// 	else if (param.disc == 0.0)
// 	{
// 		*t0 = -0.5 * param.b / param.a;
// 		*t1 = -0.5 * param.b / param.a;
// 	}
// 	else
// 	{
// 		if (param.b > 0)
// 			q = -1 * (param.b + sqrt(param.disc)) / 2;
// 		else
// 			q = -1 * (param.b - sqrt(param.disc)) / 2;
// 		*t0 = q / param.a;
// 		*t1 = param.c / q;
// 	}
// 	if (*t0 > *t1)
// 	{
// 		q = *t0;
// 		*t0 = *t1;
// 		*t1 = q;
// 	}
// 	return (true);
// }

// bool get_cyl_root(double *t0, double *t1, t_cy *cyl, t_vec3 ray_origin, t_vec3 ray_direction)
// {
// 	t_quadra param;
// 	t_vec3 a_sqrt;
// 	t_vec3 right;

// 	a_sqrt = vec_sub(ray_direction, vec_multiply(cyl->dir, vec_dot(ray_direction, cyl->dir)));
//  	param.a = vec_dot(a_sqrt, a_sqrt);
//  	right = vec_sub( vec_sub (ray_origin, cyl->origin), vec_multiply(cyl->dir, vec_dot(vec_sub(ray_origin, cyl->origin), cyl->dir)));
//  	param.b = 2 * vec_dot(a_sqrt, right);
//  	param.c = vec_dot(right, right) - (cyl->rad * cyl->rad);
//  	param.disc = param.b * param.b - 4 * param.a * param.c;
// 	if (!quad_cyl(param, t0, t1))
//  		return (false);
// 	return (true);

// }

// void	check_t(double *t, t_cy *cyl, t_vec3 ray_origin, t_vec3 ray_direction)
// {
// 	t_vec3	top;
// 	t_vec3	q;

// 	top = vec_add(cyl->origin, vec_multiply(cyl->dir, cyl->height));
// 	q = vec_add(ray_origin, vec_multiply(ray_direction, *t));
// 	if (vec_dot(cyl->dir, vec_sub(q, cyl->origin)) <= 0)
// 		*t = -1;
// 	if (vec_dot(cyl->dir, vec_sub(q, top)) >= 0)
// 		*t = -1;
// }

// double	hit_cylinder(void *cylinder, t_vec3 ray_origin, t_vec3 ray_direction)
// {
// 	t_cy	*cyl;
// 	double t0;
// 	double t1;
// 	double t;

// 	cyl = (t_cy *)cylinder;
// 	if (!get_cyl_root(&t0, &t1, cyl, ray_origin, ray_direction))
// 		return (0);
// 	if (t0 > 0)
// 		check_t(&t0, cyl, ray_origin, ray_direction);
// 	if (t1 > 0)
// 		check_t(&t1, cyl, ray_origin, ray_direction);
// 	if (t0 < 0 && t1 < 0)
// 		return (0);
// 	if (t1 < t0)
// 	{
// 		if (t1 > 0)
// 			t = t1;
// 		else
// 			t = t0;
// 	}
// 	else
// 	{
// 		if (t0 > 0)
// 			t = t0;
// 		else
// 			t = t1;
// 	}
// 	return (t);
// }