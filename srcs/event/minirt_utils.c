/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadia <jbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 17:14:49 by tshimoda          #+#    #+#             */
/*   Updated: 2022/03/24 15:09:53 by jbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incls/mini_rt.h"

t_scene	*get_scene(void)
{
	static t_scene	scene;

	if (scene.init != 1)
	{
		scene.init = 1;
		scene.amb = NULL;
		scene.cam = NULL;
		scene.lit = NULL;
		scene.select = NULL;
		scene.screen.x = 0;
		scene.screen.y = 0;
		scene.screen.is_selected = 0;
		scene.screen.obj_rot_axis = X_AXIS;
		scene.objs = ft_calloc(1, sizeof(t_vector));
		vector_init_array(scene.objs);
	}
	return (&scene);
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

void	remake_scene(t_scene *scene, t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx->img = mlx_new_image(mlx->mlx, mlx->width, mlx->height);
	ray_tracing(scene, 0, 0);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}

void	make_scene(t_scene *scene)
{
	t_mlx	*mlx;

	mlx = get_mlx();
	ray_tracing(scene, 0, 0);
	hook_collection(mlx, scene);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	mlx_loop(mlx->mlx);
}
