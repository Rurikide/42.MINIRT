/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 18:36:09 by tshimoda          #+#    #+#             */
/*   Updated: 2021/06/12 19:37:38 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0 && n / 10 == 0)
		ft_putchar_fd('-', fd);
	if (n / 10 != 0)
		ft_putnbr_fd(n / 10, fd);
	if (n % 10 < 0)
		ft_putchar_fd(-(n % 10) + '0', fd);
	else
		ft_putchar_fd((n % 10) + '0', fd);
}
