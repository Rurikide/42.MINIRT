/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadia <jbadia@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 20:17:17 by tshimoda          #+#    #+#             */
/*   Updated: 2022/02/21 16:55:20 by jbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "mini_rt.h"
# include "color.h"
# include "parsing.h"
# include "vector_3d.h"

typedef enum	e_type
{
	SPHERE, 
	CYL,
	PLANE,
}				t_type;

typedef struct s_sphere
{
	t_vec3	center;
	t_rgb	color;
	double	rad;
    t_vec3  norm;
	t_type	type;
}	            t_sphere;

// typedef	struct s_sp_set
// {
// 	double	a;
// 	double	b;
// 	double	c;
// 	double	disc;
// 	double	sqrt_disc;
// 	double	t;
// }			t_sp_set;

typedef	struct s_cam
{
	t_vec3	origin;
	t_vec3	dir;
	double	fov;
}				t_cam;

typedef struct s_scene 
{
	int		nb_obj;
    //t_amb	    *amb;
    t_cam       *cam;
    //t_lit       *light;
	t_sphere	*sp;
	//t_plan	    *pl;
	//t_cy	    *cy;

}           t_scene;


#endif