/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putcollection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 23:31:00 by tshimoda          #+#    #+#             */
/*   Updated: 2021/09/30 13:22:35 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	pf_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	pf_putchar(char c)
{
	return (write (1, &c, 1));
}

int	pf_putstr(char *str)
{
	if (str == NULL)
		return (write (1, "(null)", 6));
	return (write (1, str, pf_strlen(str)));
}
