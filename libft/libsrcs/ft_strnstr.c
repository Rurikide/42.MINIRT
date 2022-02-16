/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 11:38:01 by tshimoda          #+#    #+#             */
/*   Updated: 2021/06/05 18:42:39 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	a;
	size_t	b;
	size_t	needle_len;
	char	*haystring;

	a = 0;
	haystring = (char *)haystack;
	needle_len = ft_strlen(needle);
	if (needle_len == 0 || haystack == needle)
		return (haystring);
	while (haystring[a] && a < len)
	{
		b = 0;
		while (haystring[a + b] && needle[b]
			&& haystring[a + b] == needle[b] && a + b < len)
			b++;
		if (b == needle_len)
			return (haystring + a);
		a++;
	}
	return (0);
}
