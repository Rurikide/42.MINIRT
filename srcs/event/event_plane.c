#include "../incls/mini_rt.h"

void	plane_event(int button, t_scene *scene, t_shape *clic)
{
	t_pl	*plane;

	scene->screen.is_selected = PL;
	scene->select = clic;
	plane = (t_pl *)clic->shape;
	remake_scene(scene, get_mlx());
}

// void	plane_rotation(int keycode, t_scene *scene)
// {
// 	if (keycode == KEY_PLUS_PETIT || keycode == KEY_PLUS_GRAND)
// 		plane_yaw(keycode, scene, &((t_pl *)scene->select->shape)->dir);
// }



// void	plane_yaw(int keycode, t_scene *s, t_vec3 *plane_dir)
void	plane_rotation(int keycode, t_scene *scene)
{
	t_matrix	rotated;
	t_matrix	prod;
	t_vec3	*plane_dir;
	double		rot_step;

	plane_dir =  &((t_pl *)scene->select->shape)->dir;

	rot_step = 0.09;
	if (keycode == KEY_PLUS_GRAND)
	{
		if (scene->screen.obj_rot_axis == X_AXIS && plane_dir->x <= 0.9)
			plane_dir->x += rot_step;
		else if (scene->screen.obj_rot_axis == Y_AXIS && plane_dir->y <= 0.9)
			plane_dir->y += rot_step;
		else if (scene->screen.obj_rot_axis == Z_AXIS && plane_dir->z <= 0.9)
			plane_dir->z += rot_step;
	}	
	else if (keycode == KEY_PLUS_PETIT)
	{
		if (scene->screen.obj_rot_axis == X_AXIS && plane_dir->x >= -0.9)
			plane_dir->x -= rot_step;
		else if (scene->screen.obj_rot_axis == Y_AXIS && plane_dir->y >= -0.9)
			plane_dir->y -= rot_step;
		else if (scene->screen.obj_rot_axis == Z_AXIS && plane_dir->z >= -0.9)
			plane_dir->z -= rot_step;
	} 
	remake_scene(scene, get_mlx());
}
