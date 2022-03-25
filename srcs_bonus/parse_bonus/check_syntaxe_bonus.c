/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntaxe_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadia <jbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 15:21:02 by tshimoda          #+#    #+#             */
/*   Updated: 2022/03/25 11:11:10 by jbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incls/mini_rt.h"

void	check_if_missing_comma(char *line, int *i)
{
	int	index;

	index = *i;
	if (line[index] != ',')
		print_error_exit(get_scene(), "verify comma");
	else
		*i += 1;
}

void	check_if_missing_space(char *line, int i)
{
	if (line[i] != ' ' && line[i] != '\t')
		print_error_exit(get_scene(), "verify space");
}

void	check_if_missing_value(char *line, int i)
{
	if (!ft_isdigit(line[i]) && line[i] != '-')
		print_error_exit(get_scene(), "verify digit");
}

void	check_surplus_info(t_scene *scene, char *line, int i)
{
	if (ft_isalnum(line[i]) || ft_is_dash_comma_dot(line[i]))
		print_error_exit(scene, "too many input");
}
