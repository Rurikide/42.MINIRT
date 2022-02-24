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

t_rgb    color_multiply_rgb(t_rgb obj, t_rgb amb_lit, double ratio)
{
    t_rgb    new;

    if (ratio < 0)
        ratio = 0;
    if (ratio > 1)
        ratio = 1;
    new.r = obj.r + ((amb_lit.r - obj.r) * ratio);
    new.g = obj.g + ((amb_lit.g - obj.g) * ratio);
    new.b = obj.b + ((amb_lit.b - obj.b) * ratio);
    return (new);
}