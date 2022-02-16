/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 09:26:44 by tshimoda          #+#    #+#             */
/*   Updated: 2021/07/16 12:09:43 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_wordcount(char *s, char c)
{
	int		word_total;
	int		scan_wordornot;

	word_total = 0;
	scan_wordornot = 0;
	while (*s)
	{
		if (scan_wordornot == 0 && *s != c)
		{
			scan_wordornot = 1;
			word_total++;
		}
		else if (scan_wordornot == 1 && *s == c)
			scan_wordornot = 0;
		s++;
	}
	return (word_total);
}

static int	ft_strlenword(char *s, char c)
{
	int	len;

	len = 0;
	while (*s != c && *s)
	{
		len++;
		s++;
	}
	return (len);
}

static void	*mem_free(char **tab, int i)
{
	while (i-- > 0)
	{
		free(tab[i]);
	}
	free(tab);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		word_total;
	char	**word_table;
	int		i;

	if (!s)
		return (NULL);
	word_total = ft_wordcount((char *)s, c);
	word_table = (char **)malloc((word_total + 1) * sizeof(char *));
	if (!word_table)
		return (NULL);
	i = 0;
	while (word_total--)
	{
		while (*s == c && *s)
			s++;
		word_table[i] = ft_substr((char *)s, 0, ft_strlenword((char *)s, c));
		if (!word_table[i])
			return (mem_free(word_table, i));
		s = s + ft_strlenword((char *)s, c);
		i++;
	}
	word_table[i] = NULL;
	return (word_table);
}
