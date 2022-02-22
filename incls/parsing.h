/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 11:18:44 by tshimoda          #+#    #+#             */
/*   Updated: 2022/02/21 16:54:01 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "scene.h"

// #define SPACES " \t"
// #define WHITESPACES " \t\n\v\f\r"
// #define CHARACTERS ".,-ACLclpsy"

int		ft_table_len(char **tab);
int		get_float_len(char *line, int i);
double	parse_light_ratio(char *line, int *i);
int		get_int_len(char *line, int i);
int		parse_color_rgb(t_scene *scene, char *line, int *i);
int		parse_ambient(t_scene *scene, char *line);
int		check_parsing_type(t_scene *scene, char *line);
int		ft_is_space_tab(char c);
int		check_valid_ascii(char *line);
int		gnl_preparsing(t_scene *scene, char *file);
int		check_rt_file(char *file);
void	free_scene_exit(t_scene *scene);
//int		init_scene(t_scene *scene);
void	parse_machine(t_scene *scene, char *file);

#endif