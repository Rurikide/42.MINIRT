/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadia <jbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 14:18:39 by jbadia            #+#    #+#             */
/*   Updated: 2022/03/25 11:10:03 by jbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incls/mini_rt.h"

t_rgb	new_color(int r, int g, int b)
{
	t_rgb	rgb;

	rgb.r = r;
	rgb.g = g;
	rgb.b = b;
	return (rgb);
}

int	add_color(int color, double ratio)
{
	int	r;
	int	g;
	int	b;

	r = check_rgb(get_r(color) + ratio);
	g = check_rgb(get_g(color) + ratio);
	b = check_rgb(get_b(color) + ratio);
	return (rgb_to_int(new_color(r, g, b)));
}

int	add_3_colors(int a, int d, int c)
{
	int	r;
	int	g;
	int	b;

	r = check_rgb(get_r(a) + get_r(d) + get_r(c));
	g = check_rgb(get_g(a) + get_g(d) + get_g(c));
	b = check_rgb(get_b(a) + get_b(d) + get_b(c));
	return (rgb_to_int(new_color(r, g, b)));
}

int	add_2_colors(int a, int c)
{
	int	r;
	int	g;
	int	b;

	r = check_rgb(get_r(a) + get_r(c));
	g = check_rgb(get_g(a) + get_g(c));
	b = check_rgb(get_b(a) + get_b(c));
	return (rgb_to_int(new_color(r, g, b)));
}
