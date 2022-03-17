#include "../../incls/mini_rt.h"

double hit_plane(void *plan, t_vec3 ray_origin, t_vec3 ray_direction)
{
	t_pl	*pl;
	double	lo_po;
	double	ldotn;
	double	t;
	
	pl = (t_pl *)plan;
	lo_po = vec_dot(vec_sub(pl->origin, ray_origin), vec_normalize(pl->dir));
	ldotn = vec_dot(ray_direction, vec_normalize(pl->dir));
	t = lo_po / ldotn;
	if (t == 0.0)
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
	double t = 0;
	double h_2;
	t_vec3	top;
	t_vec3	ro_co; // ray_origin - cylindre_origin

	cyl = (t_cy *)cylinder;


	top = vec_multiply(vec_normalize(vec_multiply(cyl->dir, cyl->height)), cyl->height);
	h_2 = vec_dot(top, top); //le produit scalaire d'un v avec lui meme est égal au carré de sa longueur
	ro_co = vec_sub(ray_origin, cyl->origin);
	
	a = h_2 - vec_dot(top, ray_direction) * vec_dot(top, ray_direction);
	b = h_2 * vec_dot(ro_co, ray_direction) - vec_dot(top, vec_sub(ray_origin, cyl->origin)) * vec_dot(top, ray_direction);
	c = h_2 * vec_dot(ro_co, ro_co) - vec_dot(top, ro_co) * vec_dot(top, ro_co) - (cyl->rad) * (cyl->rad) * h_2;
	
	disc = (b * b - a * c);
	double t1 = (-b - sqrtf(disc)) / a;
	if (disc < 0) // 0 intersection 
		return (0);

	/*mon hit_p est devant moi et sur ou en dessous du top sinon c'est que je passe au dessus ou à coté? 
	Si mon t est négatif c'est que je suis en dessous du point d'origine
	Si mon t est supérieur à h_2, c'est que je suis au dessus top*/ 
	t = vec_dot(top,ro_co) + (t1) * vec_dot(top, ray_direction);
	if (t > 0 && t < h_2) 
		return (t1);
	t = calc_root(vec_dot(top, ro_co), vec_dot(top, ray_direction), h_2, t); //si je passe en dessous du top, je dois vérifier que je passe au dessus du bas du cylindre
	if (fabs(b + a * t) < sqrtf(disc))
		return (t);
	return (0);

	// t_vec3 a_sqrt = vec_sub(ray_direction, vec_multiply(cyl->dir, vec_dot(ray_direction, cyl->dir)));
 	// a = vec_dot(a_sqrt, a_sqrt);
 	// t_vec3 right = vec_sub( vec_sub (ray_origin, cyl->origin), vec_multiply(cyl->dir, vec_dot(vec_sub(ray_origin, cyl->origin), cyl->dir)));
 	// b = 2 * vec_dot(a_sqrt, right);
 	// c = vec_dot(right, right) - (cyl->rad * cyl->rad);
 	// disc = b * b - 4 * a  *c;
 	// if (disc >= 0)
 	// 	return (get_root(sqrtf(disc), b));
 	// else
 	// 	return (0);
}
