/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 20:17:17 by tshimoda          #+#    #+#             */
/*   Updated: 2022/02/23 11:04:05 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "vector_3d.h"
# include "vector_array.h"

typedef enum	e_type
{
	SPHERE = 1, 
	CYL = 2,
	PLANE = 3,
}				t_type;

typedef struct s_sphere
{
	t_vec3	center;
	t_rgb	color;
	// choisir le diametre ou le radius pour le resize???
	double	rad;
	t_vec3  norm;
	t_type	type;
}	t_sphere;

typedef struct s_shape
{
	void	*shape;
	int		type;
}t_shape;

typedef struct s_amb
{
	double	ratio;
	t_rgb color;
}	t_amb;


typedef struct s_cam
{
	t_vec3	origin;
	t_vec3	dir;
	int		fov;
}	t_cam;


typedef struct s_lit
{
	t_vec3	origin;
	double	ratio;
	// bonus t_rgb 	color;
}	t_lit;


typedef struct s_scene 
{
	int			nb_obj;
	t_amb		*amb;
	t_cam       *cam;
	// 

	t_lit       *light;
	t_vector	*shape;
}           t_scene;


#endif