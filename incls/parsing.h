/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 11:18:44 by tshimoda          #+#    #+#             */
/*   Updated: 2022/02/23 13:48:19 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "scene.h"

// #define SPACES " \t"
// #define WHITESPACES " \t\n\v\f\r"
// #define CHARACTERS ".,-ACLclpsy"

int		get_float_len(char *line, int i);
int		get_int_len(char *line, int i);

int		check_parsing_type(t_scene *scene, char *line);
int		check_valid_ascii(char *line);

int		check_rt_file(char *file);

void	free_scene_exit(t_scene *scene);
int		init_scene(t_scene *scene);
void	parse_machine(t_scene *scene, char *file);
int		gnl_preparsing(t_scene *scene, char *file);

int		ft_is_space_tab(char c);
void	ft_skip_space_tab(char *line, int *i);

int	    check_rgb_range(int r, int g, int b);
int		check_unit_range(double x, double y, double z);

// int		parse_3unit_ratio(t_scene *scene, char *line, int *i);
// int		parse_3color_rgb(t_scene *scene, char *line, int *i);
// int		parse_3coord_xyz(t_scene *scene, char *line, int *i);


int		parse_1color_rgb(char *line, int *i);
double	parse_1coord_xyz(char *line, int *i);

double	parse_light_ratio(char *line, int *i);

int		parse_ambient(t_scene *scene, char *line, int i);
int		parse_camera(t_scene *scene, char *line, int i);
int		parse_light(t_scene *scene, char *line, int i);


int		parse_field_of_view(char *line, int *i);

int		check_if_missing_value(char *line, int i);
int		check_if_missing_comma(char *line, int *i);
int		check_if_missing_space(char *line, int i);

int		check_amb_cam(t_scene *scene);
int		check_one_amb(t_scene *scene);
int		check_one_cam(t_scene *scene);
int		check_one_lit(t_scene *scene);

int		check_surplus_info(t_scene *scene, char *line, int i);

int		set_color_rgb(t_rgb *color, char *line, int *i);
int		set_coord_xyz(t_vec3 *v, char *line, int *i);

#endif