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
	else if (keycode == KEY_A || keycode == KEY_S || keycode == KEY_D || \
	keycode == KEY_W || keycode == KEY_R || keycode == KEY_T || \
	keycode == KEY_UP || keycode == KEY_DOWN || keycode == KEY_LEFT || \
	keycode == KEY_RIGHT || keycode == KEY_I || keycode == KEY_J || \
	keycode == KEY_K || keycode == KEY_L || keycode == KEY_U || \
	keycode == KEY_O)
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

void	hook_collection(t_mlx *mlx, t_scene *scene)
{
	mlx_mouse_hook(mlx->win, mouse_event, scene);
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
