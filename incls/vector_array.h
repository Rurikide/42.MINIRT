/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_array.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 11:01:35 by tshimoda          #+#    #+#             */
/*   Updated: 2022/03/18 17:03:11 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_ARRAY_H
# define VECTOR_ARRAY_H

# define VECTOR_INIT_CAPACITY 4

# include <stdlib.h>
# include <unistd.h>

typedef struct s_vector
{
	void	**elements;
	size_t	capacity;
	size_t	total;
}	t_vector;

void	vector_init_array(t_vector *v);
void	vector_add_back_element(t_vector *v, void *new_element);
void	vector_replace_element(t_vector *v, void *new, size_t index);
void	vector_delete_element(t_vector *v, size_t index);
void	vector_resize_capacity(t_vector *v, size_t new_capacity);
void	vector_free_elements(t_vector *v, void *del(void*));
#endif