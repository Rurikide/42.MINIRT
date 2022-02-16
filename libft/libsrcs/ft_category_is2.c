/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_category_is2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 22:56:35 by tshimoda          #+#    #+#             */
/*   Updated: 2021/09/30 13:29:26 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	category_is_unsign(t_data *box)
{
	box->sum += pf_putnbr_unsign((unsigned int)va_arg(box->list, unsigned int));
}

void	category_is_hexa(t_data *box)
{
	box->sum += ft_hexa((unsigned int)va_arg(box->list, int));
}

void	category_is_hexa_up(t_data *box)
{
	box->sum += ft_hexa_up((unsigned int)va_arg(box->list, int));
}

void	category_is_hexa_ptr(t_data *box)
{
	int	len;

	len = ft_hexa((unsigned long long int)va_arg(box->list, long long int));
	box->sum += len;
}
