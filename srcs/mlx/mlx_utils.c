#include "../incls/mini_rt.h"

int	key_event(int keycode, t_scene *scene)
{
	t_mlx	*mlx;

	mlx = get_mlx();
	if (keycode == KEY_ESC || keycode == KEY_Q)
	{
		mlx_destroy_image(mlx->mlx, mlx->img);
		mlx_destroy_window(mlx->mlx, mlx->win);
		exit(0);
	}
	else if ((keycode == KEY_PLUS_PETIT || keycode == KEY_PLUS_GRAND))
	{
		if (scene->screen.is_selected == CY)
			cylinder_rotation(keycode, scene);
		if (scene->screen.is_selected == PL)
			plane_rotation(keycode, scene);
	}
	// else if ((keycode == KEY_PLUS || keycode == KEY_MINUS))
	// {
	// 	if (scene->screen.is_selected == CY)
	// 		cylinder_rotation(keycode, scene);
	// 	if (scene->screen.is_selected == PL)
	// 		plane_rotation(keycode, scene);
	// }
	else if ((keycode == X_AXIS || keycode == Y_AXIS || keycode == Z_AXIS || keycode == KEY_L))
		screen_mode(keycode, scene);
	else if (keycode == KEY_A || keycode == KEY_S || keycode == KEY_D || keycode == KEY_W || keycode == KEY_R || keycode == KEY_T)
		move_cam(keycode, scene);
	else if (keycode == KEY_UP || keycode == KEY_DOWN)
		pitch_cam(keycode, scene);
	else if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
		yaw_cam(keycode, scene);
	return (0);
}

void	screen_mode(int keycode, t_scene *scene)
{
	if (keycode == KEY_L && scene->screen.is_selected == NONE)
	{
		scene->screen.is_selected = KEY_L;
		scene->select = NULL;
		printf("spotlight is selected\n");
	}
	else if ((keycode == KEY_L && scene->screen.is_selected == KEY_L))
	{
		scene->screen.is_selected = NONE;
		printf("spotlight is deselected\n");
	}
	else if (keycode == X_AXIS)
	{
		scene->screen.obj_rot_axis = X_AXIS;
		printf("Object rotation X_AXIS selected\n");
	}
	else if (keycode == Y_AXIS)
	{
		scene->screen.obj_rot_axis = Y_AXIS;
		printf("Object rotation Y_AXIS selected\n");
	}
	else if (keycode == Z_AXIS)
		{
		scene->screen.obj_rot_axis = Z_AXIS;
		printf("Object rotation Z_AXIS selected\n");
	}
}

int	click_close_window(void)
{
	// t_mlx	*mlx;

	// mlx = get_mlx();
	// mlx_destroy_image(mlx->mlx, mlx->img);
	// mlx_destroy_window(mlx->mlx, mlx->win);
	printf("clicked the red (x)\n");
	exit(0);
}

void	hook_collection(t_mlx *mlx, t_scene *scene)
{
	mlx_mouse_hook(mlx->win, click_event, scene);
	mlx_hook(mlx->win, 2, 1L << 0, key_event, scene);
	mlx_hook(mlx->win, 17, 0, click_close_window, mlx);
}

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < mlx->width && y >= 0 && y < mlx->height)
	{
		dst = mlx->adr + (y * mlx->w_len + x * (mlx->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

t_mlx	*get_mlx(void)
{
	static t_mlx	mlx;

	if (mlx.init != 1)
	{
		mlx.mlx = mlx_init();
		mlx.width = WIDTH;
		mlx.height = HEIGHT;
		mlx.img = mlx_new_image(mlx.mlx, mlx.width, mlx.height);
		mlx.adr = mlx_get_data_addr(mlx.img, &mlx.bpp, &mlx.w_len, &mlx.endian);
		mlx.win = mlx_new_window(mlx.mlx, mlx.width, mlx.height, "mini_RT");
		mlx.init = 1;
	}
	return (&mlx);
}
