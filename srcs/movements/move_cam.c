#include "../incls/mini_rt.h"

t_shape *get_hit_shape(t_scene *scene, t_ray ray)
{
	// aka intersection
	int	i;
	double distance;
	double closer;
	t_shape *shape;
	t_shape *obj;

	closer = INFINITY;
	shape = NULL;
	i = 0;
	while (i < scene->objs->total)
	{
		obj = (t_shape *)scene->objs->elements[i];
		distance = obj->hit_obj(obj->shape, ray.origin, ray.direction);
		if (distance > 0 && distance < closer)
		{
			closer = distance;
			shape = obj;
		}
		i++;
	}
	if (shape == NULL)
		return (NULL);
	return (shape);
}


int	mouse_event(int	button, int x, int y, t_scene *scene)
{
	t_ray ray;
	t_shape *clicked_on;
	t_mlx *mlx;

	mlx = get_mlx();

	// scene->screen.x = x;
	// scene->screen.y = y;
	// printf("click coordinate = (%d;%d)\n", scene->screen.x, scene->screen.y);
	ray = ray_to_pixel(scene, x, y);
	clicked_on = get_hit_shape(scene, ray);
	if (clicked_on == NULL)
	{
		scene->screen.is_selected = 0;
		scene->select = NULL;
		printf("the ray didn't hit any object\n");
		return (0);
	}
	else if (button == 2)
	{
		scene->screen.is_selected = 0;
		printf("selection cleared\n");
		return (0);
	}
	if (clicked_on->type == 1)
	{
		scene->screen.is_selected = 1;
		scene->select = clicked_on;
		t_sp *sphere = (t_sp *)clicked_on->shape;
		printf("the object is a sphere and its origin coord = (%.2f;%.2f;%.2f)\n", sphere->origin.x, sphere->origin.y, sphere->origin.z);
		if (button == 5)
		{
			sphere->rad += 0.5;
			remake_scene(scene, mlx);
		}
		if (button == 4)
		{
			if (sphere->rad > 0.5)
			sphere->rad -=0.5;
			remake_scene(scene, mlx);
		}
	}
	return (0);
}

t_matrix	new_matrix(t_vec3 origin, t_vec3 forward, t_vec3 right, t_vec3 up)
{
	t_matrix	new;

	new.d[0][0] = right.x;
	new.d[0][1] = right.y;
	new.d[0][2] = right.z;
	new.d[0][3] = 0;
	new.d[1][0] = up.x;
	new.d[1][1] = up.y;
	new.d[1][2] = up.z;
	new.d[1][3] = 0;
	new.d[2][0] = forward.x;
	new.d[2][1] = forward.y;
	new.d[2][2] = forward.z;
	new.d[2][3] = 0;
	new.d[3][0] = origin.x;
	new.d[3][1] = origin.y;
	new.d[3][2] = origin.z;
	new.d[3][3] = 1;
	return (new);
}

t_matrix	matrix_identity(void)
{
	t_scene *scene;
	t_vec3	forward;
	t_vec3	up;
	t_vec3	right;
	t_vec3	origin;

	scene = get_scene();
	forward = scene->cam->dir;

	right = new_vector(0, 0, 1);
	up = new_vector(0, 1, 0);
	origin = new_vector(0, 0, 0);
	return (new_matrix(origin, forward, right, up));
}

t_matrix	matrix_rot_y(double degrees)
{
	t_matrix		rotate;
	double		radians;

	radians = degrees * M_PI / 180;
	rotate = matrix_identity();
	rotate.d[0][0] = cos(radians);
	rotate.d[0][2] = sin(radians);
	rotate.d[2][0] = -sin(radians);
	rotate.d[2][2] = cos(radians);
	return (rotate);
}

t_matrix	matrix_rot_x(double degrees)
{
	t_matrix		rotate;
	double		radians;

	radians = degrees * M_PI / 180;
	rotate = matrix_identity();
	rotate.d[1][1] = cos(radians);
	rotate.d[1][2] = -sin(radians);
	rotate.d[2][1] = sin(radians);
	rotate.d[2][2] = cos(radians);
	return (rotate);
}

t_matrix	matrix_multi(t_matrix src, t_matrix mult)
{
	static t_matrix		out;
	int			i;
	int			j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			out.d[i][j] = src.d[i][0] * mult.d[0][j] + src.d[i][1] * mult.d[1][j] + src.d[i][2] * mult.d[2][j] + src.d[i][3] * mult.d[3][j];
			j++;
		}
		i++;
	}
	return (out);
}

void remake_scene(t_scene *scene, t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx->img = mlx_new_image(mlx->mlx, mlx->width, mlx->height);
	ray_tracing(scene);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}


void	key_translation_ad(int keycode, t_scene *scene, t_vec3 *origin)
{
	t_mlx *mlx;
	t_vec3 move;
	double step;

	mlx = get_mlx();
	step = 0.5;
	move.x = scene->cam->m.d[0][0];
	move.y = scene->cam->m.d[0][1];
	move.z = scene->cam->m.d[0][2];
	move = vec_multiply(move, step);
	if (keycode == KEY_A)
	{
		origin->x += move.x;
		origin->y += move.y;
		origin->z += move.z;
	}
	else if (keycode == KEY_D)
	{
		origin->x -= move.x;
		origin->y -= move.y;
		origin->z -= move.z;
	}
	//
	if (scene->screen.is_selected == 37)
		printf("spotlight coord = (%.2f;%.2f;%.2f)\n", origin->x, origin->y, origin->z);
	remake_scene(scene, mlx);
}

void	key_translation_ws(int keycode, t_scene *scene, t_vec3 *origin)
{
	t_mlx *mlx;
	t_vec3 move;
	double step;

	mlx = get_mlx();
	step = 0.5;
	move.x = scene->cam->m.d[2][0];
	move.y = scene->cam->m.d[2][1];
	move.z = scene->cam->m.d[2][2];
	move = vec_multiply(move, step);

	if (keycode == KEY_W)
	{
		origin->x += move.x;
		origin->y += move.y;
		origin->z += move.z;
	}
	else if (keycode == KEY_S)
	{
		origin->x -= move.x;
		origin->y -= move.y;
		origin->z -= move.z;
	}
	//
	if (scene->screen.is_selected == 37)
		printf("spotlight coord = (%.2f;%.2f;%.2f)\n", origin->x, origin->y, origin->z);
	remake_scene(scene, mlx);
}

void	key_translation_rt(int keycode, t_scene *scene, t_vec3 *origin)
{
	t_mlx *mlx;
	t_vec3 move;
	double step;

	mlx = get_mlx();
	step = 0.5;
	move.x = scene->cam->m.d[1][0];
	move.y = scene->cam->m.d[1][1];
	move.z = scene->cam->m.d[1][2];
	move = vec_multiply(move, step);

	if (keycode == KEY_T)
	{
		origin->x += move.x;
		origin->y += move.y;
		origin->z += move.z;
	}
	else if (keycode == KEY_R)
	{
		origin->x -= move.x;
		origin->y -= move.y;
		origin->z -= move.z;
	}
	//
	if (scene->screen.is_selected == 37)
		printf("spotlight coord = (%.2f;%.2f;%.2f)\n", origin->x, origin->y, origin->z);
	remake_scene(scene, mlx);
}



void	move_cam(int keycode, t_scene *scene)
{
	t_mlx *mlx;
	t_vec3 move;
	double angle = 3.5;

	mlx = get_mlx();
	if (keycode == 37 && scene->screen.is_selected != 37)
	{
		scene->screen.is_selected = 37;
		printf("spotlight is selected\n");
	}
	else if ((keycode == 37 && scene->screen.is_selected == 37))
	{
		scene->screen.is_selected = 0;
		printf("spotlight is deselected\n");
	}
	

	if (keycode == KEY_A || keycode == KEY_D)
	{
		if (scene->screen.is_selected == 0)
			key_translation_ad(keycode, scene, &scene->cam->origin);
		else if (scene->screen.is_selected == 37)
			key_translation_ad(keycode, scene, &scene->lit->origin);
		else
			key_translation_ad(keycode, scene, &((t_sp *)scene->select->shape)->origin);
	}
	else if (keycode == KEY_W || keycode == KEY_S)
	{
		if (scene->screen.is_selected == 0)
			key_translation_ws(keycode, scene, &scene->cam->origin);
		else if (scene->screen.is_selected == 37)
			key_translation_ws(keycode, scene, &scene->lit->origin);
		else
			key_translation_ws(keycode, scene, &((t_sp *)scene->select->shape)->origin);
	}
	else if (keycode == KEY_T || keycode == KEY_R)
	{
		if (scene->screen.is_selected == 0)
			key_translation_rt(keycode, scene, &scene->cam->origin);
		else if (scene->screen.is_selected == 37)
			key_translation_rt(keycode, scene, &scene->lit->origin);
		else
			key_translation_rt(keycode, scene, &((t_sp *)scene->select->shape)->origin);
	}

	// else if (keycode == KEY_UP)
	// {
	// 	t_scene *s;
	// 	t_matrix rotated;
	// 	t_matrix multiplied;
	// 	t_vec3 new;

	// 	s = get_scene();
	// 	// printf("Amatrix [2][0] = %f\n", s->cam->m.d[2][0]);
	// 	// printf("Amatrix [2][1] = %f\n", s->cam->m.d[2][1]);
	// 	// printf("Amatrix [2][2] = %f\n", s->cam->m.d[2][2]);

	// 	rotated = matrix_rot_x(-angle);
	// 	multiplied = matrix_multi(rotated, s->cam->m);
	// 	s->cam->m = multiplied;
	// 	// printf("\v");
	// 	// printf("Bmatrix [2][0] = %f\n", s->cam->m.d[2][0]);
	// 	// printf("Bmatrix [2][1] = %f\n", s->cam->m.d[2][1]);
	// 	// printf("Bmatrix [2][2] = %f\n", s->cam->m.d[2][2]);
	// 	// new = multiply_by_matrix(s->cam->origin, s->cam->m);

	// 	// printf("new.x = %f\n", new.x);
	// 	// printf("new.y = %f\n", new.y);
	// 	// printf("new.z = %f\n", new.z);

	// 	s->cam->dir.x = s->cam->m.d[2][0];
	// 	s->cam->dir.y = s->cam->m.d[2][1];
	// 	s->cam->dir.z = s->cam->m.d[2][2];
	// 	printf("PITCH LOOKING DOWN\n");
	// }
	// else if (keycode == KEY_DOWN)
	// {
	// 	t_scene *s;
	// 	t_matrix rotated;
	// 	t_matrix multiplied;
	// 	t_vec3 new;

	// 	s = get_scene();
	// 	// printf("Amatrix [2][0] = %f\n", s->cam->m.d[2][0]);
	// 	// printf("Amatrix [2][1] = %f\n", s->cam->m.d[2][1]);
	// 	// printf("Amatrix [2][2] = %f\n", s->cam->m.d[2][2]);

	// 	rotated = matrix_rot_x(angle);
	// 	multiplied = matrix_multi(rotated, s->cam->m);
	// 	s->cam->m = multiplied;
	// 	// printf("\v");
	// 	// printf("Bmatrix [2][0] = %f\n", s->cam->m.d[2][0]);
	// 	// printf("Bmatrix [2][1] = %f\n", s->cam->m.d[2][1]);
	// 	// printf("Bmatrix [2][2] = %f\n", s->cam->m.d[2][2]);
	// 	// new = multiply_by_matrix(s->cam->origin, s->cam->m);

	// 	// printf("new.x = %f\n", new.x);
	// 	// printf("new.y = %f\n", new.y);
	// 	// printf("new.z = %f\n", new.z);

	// 	s->cam->dir.x = s->cam->m.d[2][0];
	// 	s->cam->dir.y = s->cam->m.d[2][1];
	// 	s->cam->dir.z = s->cam->m.d[2][2];
	// 	printf("PITCH LOOKING UP\n");
	// }
		else if (keycode == KEY_LEFT)
	{
		t_scene *s;
		t_matrix rotated;
		t_matrix multiplied;
		t_vec3 new;

		s = get_scene();


		rotated = matrix_rot_y(-angle);
		multiplied = matrix_multi(rotated, s->cam->m);
		s->cam->m = multiplied;

		// new = multiply_by_matrix(s->cam->origin, s->cam->m);

		// printf("new.x = %f\n", new.x);
		// printf("new.y = %f\n", new.y);
		// printf("new.z = %f\n", new.z);

		s->cam->dir.x = s->cam->m.d[2][0];
		s->cam->dir.y = s->cam->m.d[2][1];
		s->cam->dir.z = s->cam->m.d[2][2];
		printf("YAW TO THE RIGHT\n");
	}
		else if (keycode == KEY_RIGHT)
	{
		t_scene *s;
		t_matrix rotated;
		t_matrix multiplied;
		t_vec3 new;

		s = get_scene();

		rotated = matrix_rot_y(angle);
		multiplied = matrix_multi(rotated, s->cam->m);
		s->cam->m = multiplied;
		// new = multiply_by_matrix(s->cam->origin, s->cam->m);

		// printf("new.x = %f\n", new.x);
		// printf("new.y = %f\n", new.y);
		// printf("new.z = %f\n", new.z);

		s->cam->dir.x = s->cam->m.d[2][0];
		s->cam->dir.y = s->cam->m.d[2][1];
		s->cam->dir.z = s->cam->m.d[2][2];
		printf("YAW TO THE LEFT\n");
	}
	remake_scene(scene, mlx);
}
