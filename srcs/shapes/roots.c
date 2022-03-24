/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   roots.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadia <jbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 14:37:18 by jbadia            #+#    #+#             */
/*   Updated: 2022/03/24 15:52:31 by jbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incls/mini_rt.h"

/*Les cap du cylindre sont comme un plan:
Si le rayon rencontre la face supérieure: t = H - ray_ori/ray_dir
Si le rayon rencontre la face inférieure: t = -ray_ori/ray_dir*/
double	calc_root(double top_roco, double toprd, double h_2, double t)
{
	double	root;

	if (t < 0)
		root = -top_roco / toprd;
	else
		root = (h_2 - top_roco) / toprd;
	return (root);
}

double	get_root(double disc, double b)
{
	double	t1;
	double	t2;
	double	t;
	double	min;
	double	max;

	t1 = (-b + disc) * 0.5;
	t2 = (-b - disc) * 0.5;
	min = fmin(t1, t2);
	max = fmax(t1, t2);
	if (min >= 0)
		t = min;
	else
		t = max;
	return (t);
}
