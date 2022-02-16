/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_3d.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 16:30:59 by tshimoda          #+#    #+#             */
/*   Updated: 2022/02/16 11:25:01 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_3D_H
# define VECTOR_3D_H

# include <math.h>
# include <unistd.h>

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;


typedef struct s_ray
{
	t_vec3 origin;
	t_vec3 direction;	
}	t_ray;

t_vec3	new_vector(double x, double y, double z);
t_vec3	vec_add(t_vec3 u, t_vec3 v);
t_vec3	vec_sub(t_vec3 u, t_vec3 v);
t_vec3	vec_multiply(t_vec3 u, double scalar);
t_vec3	vec_normalize(t_vec3 u);
t_vec3	vec_cross(t_vec3 u, t_vec3 v);
double	vec_len(t_vec3 v);
double	vec_dot(t_vec3 u, t_vec3 v);
double	vec_squared(t_vec3 v);

#endif