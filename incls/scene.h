/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 20:17:17 by tshimoda          #+#    #+#             */
/*   Updated: 2022/02/21 16:55:14 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "vector_3d.h"
# include "vector_array.h"

typedef struct s_sphere
{
	t_vec3	origin;
	t_rgb	color;
	double	rayon;
    t_vec3  hit;
    t_vec3  norm;
}	            t_sphere;

typedef struct s_amb
{
	double	ratio;
	t_rgb color;
}	t_amb;


typedef struct s_cam
{
	double	ratio;
	t_rgb color;
}	t_cam;


typedef struct s_lit
{
	double	ratio;
	t_rgb color;
}	t_lit;


typedef struct s_scene 
{
    t_amb	    *amb;
    t_cam       *cam;
    t_lit       *light;
	t_vector	*sp;
	t_vector	*pl;
	t_vector	*cy;
	//t_vector	*shape;
}           t_scene;


#endif