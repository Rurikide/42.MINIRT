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

double	calc_root(double top_roco, double toprd, double h_2, double t)
{
	double	root;

	if (t < 0)
		root = -(top_roco) / toprd;
	else
		root = (h_2 - top_roco) / toprd;
	return (root);
}

double	hit_cylinder(void *cylinder, t_vec3 ray_origin, t_vec3 ray_direction)
{
	t_cy	*cyl;
	double	a;
	double	b;
	double	c;
	double	disc;
	double height = 35.0;
	double diameter = 10;
	double t;
	double h_2;
	t_vec3	top;
	t_vec3	ro_co; // ray_origin - cylindre_origin

	cyl = (t_cy *)cylinder;

	top = vec_multiply(cyl->dir, height);
	h_2 = vec_dot(top, top); //le produit scalaire d'un v avec lui meme est égal au carré de sa longueur
	ro_co = vec_sub(ray_origin, cyl->origin);
	
	a = h_2 - vec_dot(top, ray_direction) * vec_dot(top, ray_direction);
	b = h_2 * vec_dot(ro_co, ray_direction) - vec_dot(top, vec_sub(ray_origin, cyl->origin)) * vec_dot(top, ray_direction);
	c = h_2 * vec_dot(ro_co, ro_co) - vec_dot(top, ro_co) * vec_dot(top, ro_co) - (diameter / 2) * (diameter / 2) * h_2;
	
	disc = (b * b - a * c);
	double t1 = (-b - sqrtf(disc)) / a;
	if (disc < 0) // 0 intersection 
		return (0);

	t = vec_dot(top,ro_co) + (t1) * vec_dot(top, ray_direction);
	if (t > 0 && t < h_2) // mon hit_p est devant moi et en dessous du top sinon c'est que je passe au dessus ou à coté?
		return (t1);
	t = calc_root(vec_dot(top, ro_co), vec_dot(top, ray_direction), h_2, t); //si je passe en dessous du top, je dois vérifier que je passe au dessus de l'origine
	if (fabs(b + a * t) < sqrtf(disc))
		return (t);
	return (0);
}
