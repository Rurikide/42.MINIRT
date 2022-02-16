/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 21:42:40 by tshimoda          #+#    #+#             */
/*   Updated: 2021/06/01 09:51:12 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	last_c;

	last_c = ft_strlen(s);
	while (last_c >= 0)
	{
		if (s[last_c] == (char)c)
			return ((char *)s + last_c);
		last_c--;
	}
	return (NULL);
}
