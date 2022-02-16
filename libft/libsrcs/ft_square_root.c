/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_square_root.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 23:50:49 by tshimoda          #+#    #+#             */
/*   Updated: 2022/02/16 11:03:42 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_square_root(double nb)
{
	static double	result;
	static double	root;
	static int		i;

	if (nb < 0)
	{
		printf("Error: Square root of a negative number does not exist.\n");
		exit(0);
	}
	if (nb == 0)
		return (0);
	if (i == 0)
		root = 1;
	i++;
	root = (nb / root + root) / 2;
	if (result == root)
		return (result);
	else
		result = root;
	return (ft_square_root(nb));
}
// printf to put after LINE 30
// printf("iteration = %d\n", i);
// printf("ROOT = %.10f\n", root);
// printf("RESULT = %.10f\n", result);

// int	main(void)
// {
// 	double	nb;

// 	printf("Enter a Number : ");
// 	scanf("%lf", &nb);
// 	sleep(1);
// 	printf("%.10f\n", ft_square_root(nb));
// 	return (0);
// }
