/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 19:22:55 by tshimoda          #+#    #+#             */
/*   Updated: 2022/02/06 17:12:55 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_UTILS_H
# define MATH_UTILS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

int		ft_absolute_int(int nb);
double	ft_absolute_decimal(double nb);
double	ft_power(double nb, int exponent);
double	ft_square_root(double nb);

#endif