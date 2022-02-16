/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdouble.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 20:45:40 by tshimoda          #+#    #+#             */
/*   Updated: 2022/01/19 21:02:13 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_bool	ft_strdouble(char *s1, char *s2)
{
	int		s1_len;
	int		s2_len;

	s1_len = ft_strlen(s1) - 1;
	s2_len = ft_strlen(s2) - 1;
	if (s1_len != s2_len)
		return (false);
	while (s1[s1_len] && s2[s2_len])
	{
		if (s1[s1_len] != s2[s2_len])
			return (false);
		s1_len--;
		s2_len--;
	}
	return (true);
}
