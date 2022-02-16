/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 17:40:02 by tshimoda          #+#    #+#             */
/*   Updated: 2021/09/29 19:52:33 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*fstring;
	unsigned int	len;
	unsigned int	i;

	if (s == 0 || f == 0)
		return (NULL);
	i = 0;
	len = ft_strlen(s);
	fstring = (char *)malloc(sizeof(char) * (len + 1));
	if (!fstring)
		return (NULL);
	while (s[i])
	{
		fstring[i] = (*f)(i, s[i]);
		i++;
	}
	fstring[i] = '\0';
	return (fstring);
}
