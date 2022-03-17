#include "../incls/mini_rt.h"

void	key_translation_ad(int keycode, t_scene *scene, t_vec3 *origin)
{
	t_vec3 move;

	move.x = scene->cam->m.d[0][0];
	move.y = scene->cam->m.d[0][1];
	move.z = scene->cam->m.d[0][2];
	move = vec_multiply(move, STEP);
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
	remake_scene(scene, get_mlx());
}

void	key_translation_ws(int keycode, t_scene *scene, t_vec3 *origin)
{
	t_vec3 move;

	move.x = scene->cam->m.d[2][0];
	move.y = scene->cam->m.d[2][1];
	move.z = scene->cam->m.d[2][2];
	move = vec_multiply(move, STEP);

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
	remake_scene(scene, get_mlx());
}

void	key_translation_rt(int keycode, t_scene *scene, t_vec3 *origin)
{
	t_vec3	move;

	move.x = scene->cam->m.d[1][0];
	move.y = scene->cam->m.d[1][1];
	move.z = scene->cam->m.d[1][2];
	move = vec_multiply(move, STEP);

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
	remake_scene(scene, get_mlx());
}

void	move_cam(int keycode, t_scene *scene)
{
	if (keycode == KEY_A || keycode == KEY_D)
	{
		if (scene->screen.is_selected == NONE)
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
		if (scene->screen.is_selected == NONE)
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
		if (scene->screen.is_selected == NONE)
			key_translation_rt(keycode, scene, &scene->cam->origin);
		else if (scene->screen.is_selected == SP)
			key_translation_rt(keycode, scene, &((t_sp *)scene->select->shape)->origin);
		else if (scene->screen.is_selected == PL)
			key_translation_rt(keycode, scene, &((t_pl *)scene->select->shape)->origin);
		else if (scene->screen.is_selected == KEY_L)
			key_translation_rt(keycode, scene, &scene->lit->origin);
	}
	remake_scene(scene, get_mlx());
}
