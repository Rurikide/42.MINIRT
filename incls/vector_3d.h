/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_3d.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 16:30:59 by tshimoda          #+#    #+#             */
/*   Updated: 2022/03/21 12:38:50 by tshimoda         ###   ########.fr       */
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
	t_vec3	origin;
	t_vec3	direction;	
}				t_ray;


static inline t_vec3	new_vector(double x, double y, double z)
{
	t_vec3	vector;

	vector.x = x;
	vector.y = y;
	vector.z = z;
	return (vector);
}

static inline t_vec3	vec_add(t_vec3 u, t_vec3 v)
{
	t_vec3	resultante;

	resultante.x = u.x + v.x;
	resultante.y = u.y + v.y;
	resultante.z = u.z + v.z;
	return (resultante);
}

// retourne un nouveau vecteur résultant de la soustraction.
// Utile par exemple pour calculer le Point d'intersection sur 
// une sphère (x;y;z) moins le Centre du cercle (x;y;z)
static inline t_vec3	vec_sub(t_vec3 u, t_vec3 v)
{
	t_vec3	resultante;

	resultante.x = u.x - v.x;
	resultante.y = u.y - v.y;
	resultante.z = u.z - v.z;
	return (resultante);
}

static inline t_vec3	vec_multiply(t_vec3 u, double scalar)
{
	t_vec3	resultante;

	resultante.x = u.x * scalar;
	resultante.y = u.y * scalar;
	resultante.z = u.z * scalar;
	return (resultante);
}

static inline t_vec3	vec_cross(t_vec3 u, t_vec3 v)
{
	t_vec3	resultante;

	resultante.x = (u.y * v.z) - (u.z * v.y);
	resultante.y = (u.z * v.x) - (u.x * v.z);
	resultante.z = (u.x * v.y) - (u.y * v.x);
	return (resultante);
}

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
