#ifndef COLOR_H
# define COLOR_H

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}				t_rgb;

int	rgb_to_int(t_rgb rgb);
int	check_rgb (int color);

#endif