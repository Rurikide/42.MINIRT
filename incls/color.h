/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadia <jbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 15:32:37 by jbadia            #+#    #+#             */
/*   Updated: 2022/03/24 15:33:40 by jbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}				t_rgb;

/*COLOR_RGB_C*/
int		check_rgb(int color);
int		get_r(int color);
int		get_g(int color);
int		get_b(int color);
int		rgb_to_int(t_rgb rgb);

/*COLOR_C*/
t_rgb	new_color(int r, int g, int b);
int		add_color(int color, double ratio);
t_rgb	color_multiply_rgb(t_rgb obj, t_rgb amb_lit, double ratio);
int		add_3_colors(int a, int b, int c);
int		add_2_colors(int a, int c);

static inline int	multiply_color(int color, double ratio)
{
	int	r;
	int	g;
	int	b;

	r = check_rgb(get_r(color) * ratio);
	g = check_rgb(get_g(color) * ratio);
	b = check_rgb(get_b(color) * ratio);
	return (rgb_to_int(new_color(r, g, b)));
}

#endif
