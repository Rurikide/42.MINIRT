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

	static int count;
	count++;
	printf("inside plane_yaw_func; count = %d\n", count);
	// if (keycode == KEY_LEFT)
	// 	rotated = matrix_rot_y(-ANGLE);
	// else
	// 	rotated = matrix_rot_y(ANGLE);
	// prod = matrix_product(rotated, s->cam->m);
	if (keycode == KEY_PLUS_GRAND)
	{
		plane_dir->x += 0.1;
		plane_dir->y += 0.1;
	}
	else if (keycode == KEY_PLUS_PETIT)
	{
		plane_dir->x -= 0.1;
		plane_dir->y -= 0.1;
	}
	remake_scene(s, get_mlx());
}
