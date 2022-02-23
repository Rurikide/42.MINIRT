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

int	key_event(int keycode, t_scene *scene)
{
	t_mlx *mlx;

	mlx = get_mlx();
	if (keycode == KEY_ESC || keycode == KEY_Q)
	{
		mlx_destroy_image(mlx->mlx, mlx->img);
		mlx_destroy_window(mlx->mlx, mlx->win);
		exit(0);
	}
	else if (keycode == KEY_A || keycode == KEY_S || keycode == KEY_D
		|| keycode == KEY_W)
		move_cam(keycode, scene);
	return (0);
}

int	click_close_window(void)
{
//	mlx_destroy_image(mlx, img);
//	mlx_destroy_window(mlx, win);
	printf("clicked the red (x)\n");
	exit(0);
}

void	hook_collection(t_mlx *mlx, t_scene* scene)
{
	mlx_hook(mlx->win, 2, 1L << 0, key_event, scene);

	// HOOK EVENT to close the window
	// void mlx_hook(mlx_win_list_t *win_ptr, int x_event, int x_mask, int (*f)(), void *param)
	mlx_hook(mlx->win, 17, 0, click_close_window, mlx);

}

void    my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
    char    *dst;

    if (x >= 0 && x < mlx->width && y >= 0 && y < mlx->height)
    {
        dst = mlx->adr + (y * mlx->w_len + x * (mlx->bpp / 8));
        *(unsigned int *)dst = color;
    }
}