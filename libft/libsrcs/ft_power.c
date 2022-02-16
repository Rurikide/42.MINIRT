/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 18:32:34 by tshimoda          #+#    #+#             */
/*   Updated: 2022/02/16 11:03:50 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_power(double nb, int exponent)
{
	double	result;

	result = nb;
	if (nb == 0 || exponent == 1)
		return (result);
	if (exponent == 0)
		return (1);
	if (exponent > 1)
	{
		while (exponent-- > 1)
			result *= nb;
	}
	if (exponent < 0)
	{
		result = (1 / nb);
		while (++exponent != 0)
			result *= (1 / nb);
	}
	return (result);
}

// int	main(void)
// {
// 	double	nb;
// 	int		exponent;

// 	printf("Enter a [Number] [spacebar] and its [exponent] : ");
// 	scanf("%lf %d", &nb, &exponent);
// 	sleep(1);
// 	printf("%.10f\n", ft_power(nb, exponent));
// 	return (0);
// }
