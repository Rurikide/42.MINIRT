/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadia <jbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 13:53:50 by tshimoda          #+#    #+#             */
/*   Updated: 2022/03/24 15:38:58 by jbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "vector_3d.h"
# include "vector_array.h"

typedef struct s_matrix
{
	double	d[4][4];
}				t_matrix;

typedef enum e_type
{
	SP = 1,
	CY = 2,
	PL = 3,
}	t_type;

typedef struct s_sp
{
	t_vec3	origin;
	double	rad;
	t_rgb	color;
}	t_sp;

typedef struct s_pl
{
	t_vec3	origin;
	t_vec3	dir;
	t_rgb	color;
}	t_pl;

typedef struct s_cy
{
	t_vec3	origin;
	t_vec3	dir;
	double	rad;
	double	height;
	t_rgb	color;
}	t_cy;

typedef struct s_screen
{
	int	x;
	int	y;
	int	is_selected;
	int	obj_rot_axis;
}	t_screen;

typedef struct s_shape
{
	void	*shape;
	double	(*hit_obj)(void *, t_vec3, t_vec3);
	int		type;
	t_vec3	origin;
	t_vec3	dir;
	t_rgb	color;
}	t_shape;

typedef struct s_amb
{
	double	ratio;
	t_rgb	color;
}	t_amb;

typedef struct s_cam
{
	t_vec3		origin;
	t_vec3		dir;
	int			fov;
	double		angle;
	double		view_range;
	t_matrix	m;
}	t_cam;

typedef struct s_lit
{
	t_vec3	origin;
	double	ratio;
	t_rgb	color;
}	t_lit;

typedef struct s_scene
{
	t_amb		*amb;
	t_cam		*cam;
	t_lit		*lit;
	t_vector	*objs;
	t_shape		*select;
	t_screen	screen;
	int			init;
}	t_scene;

typedef struct s_mix_lit
{
	double	shadow;
	double	kd;
	int		ambient_lit;
	int		diffuse_lit;
	int		spec_lit;
}				t_mix_lit;

typedef struct s_quadra
{
	double	a;
	double	b;
	double	c;
	double	t;
	double	t1;
}				t_quadra;

#endif