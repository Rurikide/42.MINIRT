#include "../incls/mini_rt.h"

void	pitch_cam(int keycode, t_scene *s)
{
	t_matrix	rotated;
	t_matrix	prod;
	t_vec3		new;

	if (keycode == KEY_UP)
		rotated = matrix_rot_x(-ANGLE);
	else
		rotated = matrix_rot_x(ANGLE);
	prod = matrix_product(rotated, s->cam->m);
	s->cam->m = prod;
	if ((s->cam->m.d[2][1] >= 0.90 && s->cam->m.d[2][1] <= 1.2) \
	|| (s->cam->m.d[2][1] <= -0.90 && s->cam->m.d[2][1] >= -1.2))
	{
		if ((prod.d[2][2]) >= -0.20 && (prod.d[2][2]) <= 0.20 \
		&& (prod.d[2][0]) >= -0.20 && (prod.d[2][0]) <= 0.20)
		{
			remake_scene(s, get_mlx());
			return ;
		}
	}
	s->cam->dir.x = s->cam->m.d[2][0];
	s->cam->dir.y = s->cam->m.d[2][1];
	s->cam->dir.z = s->cam->m.d[2][2];
	remake_scene(s, get_mlx());
}
void	yaw_cam(int keycode, t_scene *s)
{
	t_matrix	rotated;
	t_matrix	prod;

	if (keycode == KEY_LEFT)
		rotated = matrix_rot_y(-ANGLE);
	else
		rotated = matrix_rot_y(ANGLE);
	prod = matrix_product(rotated, s->cam->m);
	s->cam->m = prod;
	s->cam->dir.x = s->cam->m.d[2][0];
	s->cam->dir.y = s->cam->m.d[2][1];
	s->cam->dir.z = s->cam->m.d[2][2];
	remake_scene(s, get_mlx());
}

	// printf("cam dir x =%.6f \n", s->cam->dir.x);
	// printf("cam dir y =%.6f \n", s->cam->dir.y);
	// printf("cam dir z =%.6f \n", s->cam->dir.z);
	// printf("-------------------\n");
	// printf("next dir x =%.6f \n", s->cam->m.d[2][0]);
	// printf("next dir y =%.6f \n", s->cam->m.d[2][1]);
	// printf("next  dir z =%.6f \n\n", s->cam->m.d[2][2]);