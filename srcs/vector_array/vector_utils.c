/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 12:04:58 by tshimoda          #+#    #+#             */
/*   Updated: 2022/02/15 20:32:05 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incls/vector_array.h"

void	vector_free_elements(t_vector *v)
{
	free(v->elements);
	v->elements = NULL;
}
