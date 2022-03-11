#include "../../incls/mini_rt.h"

double hit_plane(void *plan, t_vec3 ray_origin, t_vec3 ray_direction)
{
	t_pl	*pl;
	double	lo_po;
	double	ldotn;
	double	t;
	
	pl = (t_pl *)plan;
	lo_po = (vec_dot(vec_sub(pl->origin, ray_origin), vec_normalize(pl->dir)));
	ldotn = vec_dot(ray_direction, vec_normalize(pl->dir));
	t = lo_po / ldotn;
	if ( t == 0.0)
		t = M_EPSILON;
	return (t);

}