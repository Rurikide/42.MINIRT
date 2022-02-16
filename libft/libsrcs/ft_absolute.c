/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_absolute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 19:32:57 by tshimoda          #+#    #+#             */
/*   Updated: 2022/02/11 15:38:30 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_utils.h"

int	ft_absolute_int(int nb)
{
	if ((double)nb > 2147483647 || (double)nb < -2147483748)
		return (-1);
	if (nb < 0)
		nb *= -1;
	return (nb);
}

double	ft_absolute_decimal(double nb)
{
	if (nb < 0)
		nb *= -1;
	return (nb);
}
