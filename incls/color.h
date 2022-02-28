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
t_rgb	new_color(int r, int g, int b);
int add_color(int color, double ratio);
t_rgb    color_multiply_rgb(t_rgb obj, t_rgb amb_lit, double ratio);
int multiply_color(int color, double ratio);
int	add_3_colors(int a, int b, int c);



#endif