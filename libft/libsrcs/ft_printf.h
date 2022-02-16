/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 14:46:17 by tshimoda          #+#    #+#             */
/*   Updated: 2021/09/30 13:29:01 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>

typedef struct s_data
{
	va_list		list;
	const char	*str;
	char		*scan_type;
	int			vernier;
	int			pos;
	int			sum;
}		t_data;

int		ft_printf(const char *str, ...);
void	ft_parsef(t_data *box);
void	ft_category_scanner(t_data *box);
void	category_is_char(t_data *box);
void	category_is_string(t_data *box);
void	category_is_decint(t_data *box);
void	category_is_unsign(t_data *box);
void	category_is_hexa(t_data *box);
void	category_is_hexa_up(t_data *box);
void	category_is_hexa_ptr(t_data *box);
void	category_is_modulo(t_data *box);
int		pf_strlen(char *str);
int		pf_putchar(char c);
int		pf_putstr(char *str);
int		pf_putnbr(int n);
int		pf_putnbr_unsign(unsigned int n);
int		ft_hexa(unsigned long long int nb);
int		ft_hexa_up(unsigned long long int nb);

#endif