/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skip_space_tab.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 22:12:53 by tshimoda          #+#    #+#             */
/*   Updated: 2022/03/21 12:38:02 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_skip_space_tab(char *line, int *i)
{
	int	move_forward;
	int	index;

	move_forward = 0;
	index = *i;
	while (ft_is_space_tab(line[index]))
	{
		index++;
		move_forward++;
	}
	*i += move_forward;
}
