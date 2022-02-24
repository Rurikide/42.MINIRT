#ifndef COLOR_H
# define COLOR_H

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}				t_rgb;

/*COLOR_RGB_C*/
int	check_rgb (int color);
int	get_r(int color);
int	get_g(int color);
int	get_b(int color);
int	rgb_to_int(t_rgb rgb);

/*COLOR_C*/
int		add_color(int color_a, int color_b);
t_rgb	new_color(int r, int g, int b);



#endif