#include "../incls/mini_rt.h"

void	plane_event(int button, t_scene *scene, t_shape *clic)
{
	t_pl	*plane;

	scene->screen.is_selected = PL;
	scene->select = clic;
	plane = (t_pl *)clic->shape;
	remake_scene(scene, get_mlx());
}

void	plane_rotation(int keycode, t_scene *scene)
{
	if (keycode == KEY_PLUS_PETIT || keycode == KEY_PLUS_GRAND)
		plane_yaw(keycode, scene, &((t_pl *)scene->select->shape)->dir);
}



void	plane_yaw(int keycode, t_scene *s, t_vec3 *plane_dir)
{
	t_matrix	rotated;
	t_matrix	prod;
	double		rot_step;

	rot_step = 0.1;
	if (keycode == KEY_PLUS_GRAND)
	{
		if (s->screen.obj_rot_axis == X_AXIS && plane_dir->x <= 0.8)
			plane_dir->x += rot_step;
		else if (s->screen.obj_rot_axis == Y_AXIS && plane_dir->y <= 0.8)
			plane_dir->y += rot_step;
		else if (s->screen.obj_rot_axis == Z_AXIS && plane_dir->z <= 0.8)
			plane_dir->z += rot_step;
	}	
	else if (keycode == KEY_PLUS_PETIT)
	{
		if (s->screen.obj_rot_axis == X_AXIS && plane_dir->x >= -0.8)
			plane_dir->x -= rot_step;
		else if (s->screen.obj_rot_axis == Y_AXIS && plane_dir->y >= -0.8)
			plane_dir->y -= rot_step;
		else if (s->screen.obj_rot_axis == Z_AXIS && plane_dir->z >= -0.8)
			plane_dir->z -= rot_step;
	}
	remake_scene(s, get_mlx());
}
