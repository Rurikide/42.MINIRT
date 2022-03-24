/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation_signal.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 17:08:35 by tshimoda          #+#    #+#             */
/*   Updated: 2022/03/21 14:04:55 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incls/mini_rt.h"

void	translation_signal_ad(int keycode, t_scene *scene)
{
	if (scene->screen.is_selected == NONE)
		key_translation_ad(keycode, scene, &scene->cam->origin);
	else if (scene->screen.is_selected == SP)
		key_translation_ad(keycode, scene, \
		&((t_sp *)scene->select->shape)->origin);
	else if (scene->screen.is_selected == CY)
		key_translation_ad(keycode, scene, \
		&((t_cy *)scene->select->shape)->origin);
	else if (scene->screen.is_selected == PL)
		key_translation_ad(keycode, scene, \
		&((t_pl *)scene->select->shape)->origin);
	else if (scene->screen.is_selected == KEY_L)
		key_translation_ad(keycode, scene, &scene->lit->origin);
}

void	translation_signal_ws(int keycode, t_scene *scene)
{
	if (scene->screen.is_selected == NONE)
		key_translation_ws(keycode, scene, &scene->cam->origin);
	else if (scene->screen.is_selected == SP)
		key_translation_ws(keycode, scene, \
		&((t_sp *)scene->select->shape)->origin);
	else if (scene->screen.is_selected == CY)
		key_translation_ws(keycode, scene, \
		&((t_cy *)scene->select->shape)->origin);
	else if (scene->screen.is_selected == PL)
		key_translation_ws(keycode, scene, \
		&((t_pl *)scene->select->shape)->origin);
	else if (scene->screen.is_selected == KEY_L)
		key_translation_ws(keycode, scene, &scene->lit->origin);
}

void	translation_signal_rt(int keycode, t_scene *scene)
{
	if (scene->screen.is_selected == NONE)
		key_translation_rt(keycode, scene, &scene->cam->origin);
	else if (scene->screen.is_selected == SP)
		key_translation_rt(keycode, scene, \
		&((t_sp *)scene->select->shape)->origin);
	else if (scene->screen.is_selected == CY)
		key_translation_rt(keycode, scene, \
		&((t_cy *)scene->select->shape)->origin);
	else if (scene->screen.is_selected == PL)
		key_translation_rt(keycode, scene, \
		&((t_pl *)scene->select->shape)->origin);
	else if (scene->screen.is_selected == KEY_L)
		key_translation_rt(keycode, scene, &scene->lit->origin);
}

void	translation_signal_handler(int keycode, t_scene *scene)
{
	if (keycode == KEY_A || keycode == KEY_D)
	{
		translation_signal_ad(keycode, scene);
	}
	else if (keycode == KEY_W || keycode == KEY_S)
	{
		translation_signal_ws(keycode, scene);
	}
	else if (keycode == KEY_T || keycode == KEY_R)
	{
		translation_signal_rt(keycode, scene);
	}
}
