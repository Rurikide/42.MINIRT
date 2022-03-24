/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_3d2.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 14:56:53 by tshimoda          #+#    #+#             */
/*   Updated: 2022/03/24 15:08:29 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_3D2_H
# define VECTOR_3D2_H

# include <math.h>
# include <unistd.h>
# include "vector_3d.h"

// reçoit le pointeur du vecteur v et modifie ses composantes (x;y;z) 
// afin de le normaliser ainsi simplifier les prochains calculs
static inline t_vec3	vec_normalize(t_vec3 v)
{
	double	grandeur;
	t_vec3	resultante;

	grandeur = sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
	resultante.x = v.x / grandeur;
	resultante.y = v.y / grandeur;
	resultante.z = v.z / grandeur;
	return (resultante);
}

static inline double	vec_len(t_vec3 v)
{
	double	grandeur;

	grandeur = (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
	return (grandeur);
}

// retourne le produit croisé de deux vecteurs qui est une 
// distance/nombre par rapport au point d'origine d'un vecteur 
static inline double	vec_dot(t_vec3 u, t_vec3 v)
{
	double	distance;

	distance = (u.x * v.x) + (u.y * v.y) + (u.z * v.z);
	return (distance);
}

static inline t_vec3	multiply_2_vec(t_vec3 u, t_vec3 v)
{
	t_vec3	resultante;

	resultante.x = (u.x * v.x);
	resultante.y = (u.y * v.y);
	resultante.z = (u.z * v.z);
	return (resultante);
}

#endif