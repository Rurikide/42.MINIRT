#include "../incls/color.h"

int	check_rgb (int color)
{
	if (color > 255)
		return (255);
	else if (color < 0)
		return (0);
	else
		return (color);
}

int    get_r(int color)
{
    return ((color >> 16) & 0xFF);
}

int    get_g(int color)
{
    return ((color >> 8) & 0xFF);
}

int    get_b(int color)
{
    return (color & 0xFF);
}

int	rgb_to_int(t_rgb rgb)
{
	int	color;

	color = rgb.r << 16 | rgb.g << 8 | rgb.b;
	return (color);
}

t_rgb int_to_rgb(int color)
{
	t_rgb rgb;

	rgb.r = get_r(color);
	rgb.g = get_g(color);
	rgb.b = get_b(colo);
	return (rgb);
}

