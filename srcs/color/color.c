#include "../../incls/mini_rt.h"

int	add_color(int color_1, int color_2)
{
	return (color_1 + color_2);
}

t_rgb	new_color(int r, int g, int b)
{
	t_rgb	rgb;

	rgb.r = r;
	rgb.g = g;
	rgb.b = b;

	return (rgb);
}
