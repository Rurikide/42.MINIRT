/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 11:18:44 by tshimoda          #+#    #+#             */
/*   Updated: 2022/02/16 17:18:13 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "color.h"

typedef struct s_amb
{
	double	ratio;
	t_rgb color;
}	t_amb;

typedef struct s_parse
{
	t_amb	*amb;
}	t_parse;

void	parse_machine(t_parse *data, char *file);
int		ft_is_valid_file(char *file);
void    ft_read_file(t_parse *data, char *file);
void    ft_scan_line(t_parse *data, char *line);
#endif