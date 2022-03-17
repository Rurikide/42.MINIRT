#include "../incls/mini_rt.h"

void	sphere_resize(int button, t_scene *scene, t_shape *clic)
{
	t_sp	*sphere;

	scene->screen.is_selected = SP;
	scene->select = clic;
	sphere = (t_sp *)clic->shape;
	if (button == ROULETTE_FORWARD)
	{
		sphere->rad += 0.5;
		remake_scene(scene, get_mlx());
	}
	if (button == ROULETTE_BACKWARD)
	{
		if (sphere->rad > 0.5)
			sphere->rad -= 0.5;
		remake_scene(scene, get_mlx());
	}
}