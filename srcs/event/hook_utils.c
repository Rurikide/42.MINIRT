/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadia <jbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 15:27:08 by tshimoda          #+#    #+#             */
/*   Updated: 2022/03/24 15:43:42 by jbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incls/mini_rt.h"

int	key_event(int key, t_scene *scene)
{
	if (key == KEY_ESC || key == KEY_Q)
		close_minirt();
	else if ((key == KEY_PLUS_PETIT || key == KEY_PLUS_GRAND))
	{
		if (scene->screen.is_selected == CY)
			cylinder_rotation(key, scene);
		if (scene->screen.is_selected == PL)
			plane_rotation(key, scene);
	}
	else if (key == KEY_PLUS || key == KEY_MINUS)
		cylinder_height(key, scene);
	else if ((key == X_AXIS || key == Y_AXIS || key == Z_AXIS || key == KEY_L))
		screen_mode(key, scene);
	else if (key == KEY_A || key == KEY_S || key == KEY_D || \
			key == KEY_W || key == KEY_R || key == KEY_T)
		translation_signal_handler(key, scene);
	else if (key == KEY_UP || key == KEY_DOWN)
		pitch_cam(key, scene);
	else if (key == KEY_LEFT || key == KEY_RIGHT)
		yaw_cam(key, scene);
	return (0);
}

void	screen_mode(int keycode, t_scene *scene)
{
	if (keycode == KEY_L && scene->screen.is_selected == NONE)
	{
		scene->screen.is_selected = KEY_L;
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

int	hook_collection(t_mlx *mlx, t_scene *scene)
{
	mlx_mouse_hook(mlx->win, click_event, scene);
	mlx_hook(mlx->win, 2, 1L << 0, key_event, scene);
	mlx_hook(mlx->win, 17, 0, click_close_window, mlx);
	return (0);
}
