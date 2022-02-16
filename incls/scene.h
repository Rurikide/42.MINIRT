/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 20:17:17 by tshimoda          #+#    #+#             */
/*   Updated: 2022/02/16 15:04:47 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "vector_3d.h"

typedef struct s_circle
{
	double	x;
	double	y;
	double	z;
	float	radius;
	int		init;
	int		color;
}	t_circle;

typedef struct s_sphere
{
	t_vec3	origin;
	t_vec3	color;
	double	rayon;
}	t_sphere;

typedef struct s_main
{
	t_circle	*circle;
	int			nb;
}	t_main;

#endif