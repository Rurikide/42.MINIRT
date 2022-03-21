/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 13:09:13 by tshimoda          #+#    #+#             */
/*   Updated: 2022/03/21 13:09:14 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "scene.h"

//		scene_utils.c
void	free_scene(t_scene *scene);
t_scene	*get_scene(void);

//		parse.c
void	parse_machine(t_scene *scene, char *file);
int		gnl_preparsing(t_scene *scene, char *file);
int		check_parsing_type(t_scene *scene, char *line);

//		parse_utils.c
int		get_float_len(char *line, int i);
int		get_int_len(char *line, int i);
void	print_error_exit(t_scene *scene, char *msg);

//		check_valid_file.c
int		check_valid_ascii(t_scene *sc, char *line, int i, int j);
int		check_rt_file(char *file);

//		parse_settings.c
double	parse_light_ratio(char *line, int *i);
double	parse_dimension(char *line, int *i);
int		parse_field_of_view(char *line, int *i);

//		parse_rgb.c
void	check_rgb_range(int r, int g, int b);
int		parse_1color_rgb(char *line, int *i);
void	set_color_rgb(t_rgb *color, char *line, int *i);

//		parse_xyz.c
void	check_unit_range(t_vec3 *unit);
double	parse_1coord_xyz(char *line, int *i);
void	set_coord_xyz(t_vec3 *v, char *line, int *i);

//		check_ambcamlit.c
void	check_amb_cam_lit(t_scene *scene);
void	check_one_amb(t_scene *scene);
void	check_one_cam(t_scene *scene);
void	check_one_lit(t_scene *scene);

//		check_syntaxe.c
void	check_if_missing_value(char *line, int i);
void	check_if_missing_comma(char *line, int *i);
void	check_if_missing_space(char *line, int i);
void	check_surplus_info(t_scene *scene, char *line, int i);

//		parse_ambcamlit.c
void	parse_ambient(t_scene *scene, char *line, int i);
void	parse_camera(t_scene *scene, char *line, int i);
void	parse_light(t_scene *scene, char *line, int i);

//		parse_shape.c
void	parse_sphere(t_scene *scene, char *line, int i);
void	parse_cylinder(t_scene *scene, char *line, int i);
void	parse_cylinder2(t_shape *new, t_cy *cy);
void	parse_plane(t_scene *scene, char *line, int i);
#endif