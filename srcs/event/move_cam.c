#include "../incls/mini_rt.h"

t_shape *get_hit_shape(t_scene *scene, t_ray ray)
{
	size_t	i;
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
		if (distance > M_EPSILON && distance < closer)
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
	t_shape	*clicked_on;
	t_ray	ray;
	t_mlx	*mlx;

	mlx = get_mlx();
	ray = ray_generator(scene, x, y);
	clicked_on = get_hit_shape(scene, ray);
	if (clicked_on == NULL)
	{
		scene->screen.is_selected = 0;
		scene->select = NULL;
		printf("the ray didn't hit any object\n");
		return (0);
	}
	else if (button == MOUSE_RIGHT)
	{
		scene->screen.is_selected = NO;
		printf("selection cleared\n");
		return (0);
	}
	if (clicked_on->type == SP)
	{
		scene->screen.is_selected = YES;
		scene->select = clicked_on;
		t_sp *sphere = (t_sp *)clicked_on->shape;
		printf("the object is a sphere and its origin coord = (%.2f;%.2f;%.2f)\n", sphere->origin.x, sphere->origin.y, sphere->origin.z);
		if (button == ROULETTE_FORWARD)
		{
			sphere->rad += 0.5;
			remake_scene(scene, mlx);
		}
		if (button == ROULETTE_BACKWARD)
		{
			if (sphere->rad > 0.5)
				sphere->rad -=0.5;
			remake_scene(scene, mlx);
		}
	}
	if (clicked_on->type == PL)
	{
		scene->screen.is_selected = PL;
		scene->select = clicked_on;
		t_pl *plan = (t_pl *)clicked_on->shape;
		printf("the object is a plan and its origin coord = (%.2f;%.2f;%.2f)\n", plan->origin.x, plan->origin.y, plan->origin.z);
		remake_scene(scene, mlx);
	}
	return (0);
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
	if (scene->screen.is_selected == KEY_L)
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
	double angle = 3.5;

	mlx = get_mlx();
	if (keycode == KEY_L && scene->screen.is_selected == NO)
	{
		scene->screen.is_selected = 37;
		printf("spotlight is selected\n");
	}
	else if ((keycode == KEY_L && scene->screen.is_selected == KEY_L))
	{
		scene->screen.is_selected = NO;
		printf("spotlight is deselected\n");
	}
	if (keycode == KEY_A || keycode == KEY_D)
	{
		if (scene->screen.is_selected == 0)
			key_translation_ad(keycode, scene, &scene->cam->origin);
		else if (scene->screen.is_selected == SP)
			key_translation_ad(keycode, scene, &((t_sp *)scene->select->shape)->origin);	
		else if (scene->screen.is_selected == PL)
			key_translation_ad(keycode, scene, &((t_pl *)scene->select->shape)->origin);
		else if (scene->screen.is_selected == KEY_L)
			key_translation_ad(keycode, scene, &scene->lit->origin);
	}
	else if (keycode == KEY_W || keycode == KEY_S)
	{
		if (scene->screen.is_selected == 0)
			key_translation_ws(keycode, scene, &scene->cam->origin);
		else if (scene->screen.is_selected == SP)
			key_translation_ws(keycode, scene, &((t_sp *)scene->select->shape)->origin);
		else if (scene->screen.is_selected == PL)
			key_translation_ws(keycode, scene, &((t_pl *)scene->select->shape)->origin);
		else if (scene->screen.is_selected == KEY_L)
			key_translation_ws(keycode, scene, &scene->lit->origin);
	}
	else if (keycode == KEY_T || keycode == KEY_R)
	{
		if (scene->screen.is_selected == 0)
			key_translation_rt(keycode, scene, &scene->cam->origin);
		else if (scene->screen.is_selected == SP)
			key_translation_rt(keycode, scene, &((t_sp *)scene->select->shape)->origin);
		else if (scene->screen.is_selected == PL)
			key_translation_rt(keycode, scene, &((t_pl *)scene->select->shape)->origin);
		else if (scene->screen.is_selected == KEY_L)
			key_translation_rt(keycode, scene, &scene->lit->origin);
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
