/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 11:18:44 by tshimoda          #+#    #+#             */
/*   Updated: 2022/02/19 16:58:04 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "color.h"

#define SPACES " \t"
#define WHITESPACES " \t\n\v\f\r"
#define CHARACTERS ".,ACLclpsy"


int		check_parsing_type(t_scene *scene, char *line);
int		ft_is_space_tab(char c);
int		check_valid_ascii(char *line);
int		gnl_preparsing(t_scene *scene, char *file);
int		check_rt_file(char *file);
void	parse_machine(t_scene *scene, char *file);
void	free_scene_exit(t_scene *scene);
int		init_scene(t_scene *scene);

#endif