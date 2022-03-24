/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadia <jbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 14:33:29 by jbadia            #+#    #+#             */
/*   Updated: 2022/03/24 14:33:31 by jbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incls/mini_rt.h"

t_rgb	get_diffuse_lit(t_rgb obj, t_scene *scene)
{
	t_rgb	color;

	color.r = (scene->lit->ratio * 255 * obj.r) / 255;
	color.g = (scene->lit->ratio * 255 * obj.g) / 255;
	color.b = (scene->lit->ratio * 255 * obj.b) / 255;
	return (color);
}

t_rgb	get_spec_lit(t_rgb obj,	double ks)
{
	t_rgb	color;

	color.r = (ks * 255 * obj.r) / 255;
	color.g = (ks * 255 * obj.g) / 255;
	color.b = (ks * 255 * obj.b) / 255;
	return (color);
}

t_rgb	get_ambient_lit(t_scene *scene, t_rgb obj)
{
	t_rgb	color;

	color.r = (scene->amb->ratio * scene->amb->color.r * obj.r) / 255;
	color.g = (scene->amb->ratio * scene->amb->color.g * obj.g) / 255;
	color.b = (scene->amb->ratio * scene->amb->color.b * obj.b) / 255;
	return (color);
}
