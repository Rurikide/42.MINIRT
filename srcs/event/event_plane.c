#include "../incls/mini_rt.h"

void	plane_event(int button, t_scene *scene, t_shape *clic)
{
	t_pl	*plane;

	scene->screen.is_selected = PL;
	scene->select = clic;
	plane = (t_pl *)clic->shape;
	remake_scene(scene, get_mlx());
}