/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_tool.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadia <jbadia@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 16:34:02 by tshimoda          #+#    #+#             */
/*   Updated: 2022/02/21 09:20:43 by jbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incls/vector_3d.h"

// reçoit le pointeur du vecteur v et modifie ses composantes (x;y;z) 
// afin de le normaliser ainsi simplifier les prochains calculs
t_vec3	vec_normalize(t_vec3 v)
{
	double		grandeur;
	t_vec3 		resultante;

	grandeur = sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
	resultante.x = v.x / grandeur;
	resultante.y = v.y / grandeur;
	resultante.z = v.z / grandeur;
	return (resultante);
}

// retourne la grandeur/longueur d'un vecteur
double	vec_squared(t_vec3 v)
{
	double	grandeur;

	grandeur = (v.x * v.x + v.y * v.y + v.z * v.z);
	return (grandeur);
}

double	vec_len(t_vec3 v)
{
	double	grandeur;

	grandeur = (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
	return (grandeur);
}

// retourne le produit croisé de deux vecteurs qui est une 
// distance/nombre par rapport au point d'origine d'un vecteur 
double	vec_dot(t_vec3 u, t_vec3 v)
{
	double	distance;

	distance = (u.x * v.x) + (u.y * v.y) + (u.z * v.z);
	return (distance);
}

t_vec3	multiply_2_vec(t_vec3 u, t_vec3 v)
{
	t_vec3	resultante;

	resultante.x = (u.x * v.x);
	resultante.y = (u.y * v.y);
	resultante.z = (u.z * v.z);
	return (resultante);
}
