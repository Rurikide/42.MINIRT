#include "../incls/mini_rt.h"

void	cylinder_event(int button, t_scene *scene, t_shape *clic)
{
	t_cy	*cylinder;

	scene->screen.is_selected = CY;
	scene->select = clic;
	cylinder = (t_cy *)clic->shape;
	
	
	if (button == ROULETTE_FORWARD)
	{
		cylinder->rad += 0.5;
		remake_scene(scene, get_mlx());
	}
	if (button == ROULETTE_BACKWARD)
	{
		if (cylinder->rad > 0.5)
			cylinder->rad -= 0.5;
		remake_scene(scene, get_mlx());
	}
}

void	cylinder_rotation(int keycode, t_scene *scene)
{
	t_matrix	rotated;
	t_matrix	prod;
	t_vec3	*cylinder_dir;
	double		rot_step;

	cylinder_dir =  &((t_pl *)scene->select->shape)->dir;

	rot_step = 0.09;
	if (keycode == KEY_PLUS_GRAND)
	{
		if (scene->screen.obj_rot_axis == X_AXIS && cylinder_dir->x <= 0.9)
			cylinder_dir->x += rot_step;
		else if (scene->screen.obj_rot_axis == Y_AXIS && cylinder_dir->y <= 0.9)
			cylinder_dir->y += rot_step;
		else if (scene->screen.obj_rot_axis == Z_AXIS && cylinder_dir->z <= 0.9)
			cylinder_dir->z += rot_step;
	}	
	else if (keycode == KEY_PLUS_PETIT)
	{
		if (scene->screen.obj_rot_axis == X_AXIS && cylinder_dir->x >= -0.8)
			cylinder_dir->x -= rot_step;
		else if (scene->screen.obj_rot_axis == Y_AXIS && cylinder_dir->y >= -0.9)
			cylinder_dir->y -= rot_step;
		else if (scene->screen.obj_rot_axis == Z_AXIS && cylinder_dir->z >= -0.9)
			cylinder_dir->z -= rot_step;
	} 
	remake_scene(scene, get_mlx());
}
