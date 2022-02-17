/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadia <jbadia@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 20:17:17 by tshimoda          #+#    #+#             */
/*   Updated: 2022/02/16 15:34:09 by jbadia           ###   ########.fr       */
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

// typedef struct s_scene 
// {
//     t_amb	    *amb;
//     t_cam       *cam;
//     t_lit       *light;
// 	t_sphere	*sp;
// 	t_plan	    *pl;
// 	t_cy	    *cy;
// }           t_scene;


#endif