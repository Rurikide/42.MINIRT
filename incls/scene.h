/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 20:17:17 by tshimoda          #+#    #+#             */
/*   Updated: 2022/02/19 14:18:51 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "mini_rt.h"
# include "color.h"
# include "parsing.h"
# include "vector_3d.h"

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

typedef struct s_scene 
{
    t_amb	    *amb;
    t_cam       *cam;
    t_lit       *light;
	t_sphere	*sp;
	t_plan	    *pl;
	t_cy	    *cy;
}           t_scene;


#endif