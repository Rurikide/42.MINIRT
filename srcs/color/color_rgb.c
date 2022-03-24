/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadia <jbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 14:16:47 by jbadia            #+#    #+#             */
/*   Updated: 2022/03/24 14:18:18 by jbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incls/mini_rt.h"

int	check_rgb(int color)
{
	if (color > 255)
		return (255);
	else if (color < 0)
		return (0);
	else
		return (color);
}

int	get_r(int color)
{
	return ((color >> 16) & 0xFF);
}

int	get_g(int color)
{
	return ((color >> 8) & 0xFF);
}

int	get_b(int color)
{
	return (color & 0xFF);
}

int	rgb_to_int(t_rgb rgb)
{
	return (rgb.r << 16 | rgb.g << 8 | rgb.b);
}
