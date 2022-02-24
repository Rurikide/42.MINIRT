#include "../incls/mini_rt.h"

void remake_scene(t_scene *scene, t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx->img = mlx_new_image(mlx->mlx, mlx->width, mlx->height);
	ray_tracing(scene);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}

void	move_cam(int keycode, t_scene *scene)
{
	t_mlx *mlx;

	mlx = get_mlx();
	if (keycode == KEY_A)
		scene->cam->origin.x -= 5;
	else if (keycode == KEY_D)
		scene->cam->origin.x += 5;
	else if (keycode == KEY_S)
		scene->cam->origin.y -= 5;
	else if (keycode == KEY_W)
		scene->cam->origin.y += 5;
	remake_scene(scene, mlx);
}