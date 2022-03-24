#include "../../incls/mini_rt.h"

/*((origin_pl - origin_ray) ° norm_pl) / (ray_dir ° norm_pl)*/
double hit_plane(void *plan, t_vec3 ray_origin, t_vec3 ray_direction)
{
	t_pl	*pl;
	double	a;
	double	b;
	double	t;
	
	pl = (t_pl *)plan;
	a = vec_dot(vec_sub(pl->origin, ray_origin), vec_normalize(pl->dir));
	b = vec_dot(ray_direction, vec_normalize(pl->dir));
	t = a / b;
	return (t);
}

t_vec3	get_cyl_norm(t_vec3 hit_p, t_cy *cyl)
{
	double	d;
	t_vec3	sum;
	t_vec3	norm;
	t_vec3	top;

	// top = vec_multiply(vec_normalize(vec_multiply(cyl->dir, cyl->height)), cyl->height);
	//top = vec_add(cyl->origin, vec_multiply(cyl->dir, cyl->height));
	top = vec_add(cyl->origin, vec_multiply(cyl->dir, cyl->height));

	if (vec_len(vec_sub(hit_p, cyl->origin)) < cyl->rad)
	{
		norm = vec_multiply(cyl->dir, -1);
		printf("dir \n");
	}
	else if (vec_len(vec_sub(hit_p, top)) < cyl->rad)
	{
		norm = cyl->dir;
		printf("- dir \n");
	}
	else
	{
		d = vec_dot(vec_sub(hit_p, cyl->origin), cyl->dir);
		sum = vec_add(cyl->origin, vec_multiply(cyl->dir, d));; // origin ou dir ??
		norm = vec_normalize(vec_sub(hit_p, sum));
	}
	return (norm);
}

/*Les cap du cylindre sont comme un plan:
Si le rayon rencontre la face supérieure: t= H - ray_ori/ray_dir
Si le rayon rencontre la face inférieure: t= -ray_ori/ray_dir*/
double	calc_root(double top_roco, double toprd, double h_2, double t)
{
	double	root;

	if (t < 0)
		root = -top_roco/ toprd;
	else
		root = (h_2 - top_roco) / toprd;
	return (root);
}

/*Si le discriminant est inférieur à 0, il n'y a pas d'intersection
Si param.t est supérieur à 0 mais inférieur à la H, le rayon touche le corps du cylindre
Sinon je vérifie si je suis dans les caps*/
double	hit_cylinder(void *cylinder, t_vec3 ray_origin, t_vec3 ray_direction)
{
	t_cy		*cyl;
	t_quadra	param;
	double		h_2;
	t_vec3		top;
	t_vec3		ro_co;

	cyl = (t_cy *)cylinder;
	top = vec_multiply(vec_normalize(vec_multiply(cyl->dir, cyl->height)), cyl->height);
	//top = vec_add(cyl->origin, vec_multiply(cyl->dir, cyl->height));
	h_2 = vec_dot(top, top);
	ro_co = vec_sub(ray_origin, cyl->origin);

	param.a = h_2 - vec_dot(top, ray_direction) * vec_dot(top, ray_direction);

	param.b = h_2 * vec_dot(ro_co, ray_direction) - vec_dot(top, ro_co) * vec_dot(top, ray_direction);

	param.c = h_2 * vec_dot(ro_co, ro_co) - vec_dot(top, ro_co) * vec_dot(top, ro_co) - (cyl->rad) * (cyl->rad) * h_2;

	param.disc = (param.b * param.b - param.a * param.c);
	if (param.disc < 0) 
		return (0);
	param.t1 = (-param.b - sqrtf(param.disc)) / param.a;
	param.t = vec_dot(top,ro_co) + (param.t1) * vec_dot(top, ray_direction);
	if (param.t > 0 && param.t < h_2) 
		return (param.t1);
	param.t = calc_root(vec_dot(top, ro_co), vec_dot(top, ray_direction), h_2, param.t);
	if (fabs(param.b + param.a * param.t) < sqrtf(param.disc))
		return (param.t);
	return (0);
}
