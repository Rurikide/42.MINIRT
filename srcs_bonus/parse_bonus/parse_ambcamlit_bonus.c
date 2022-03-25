/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambcamlit_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadia <jbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 15:23:11 by tshimoda          #+#    #+#             */
/*   Updated: 2022/03/25 11:11:17 by jbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incls/mini_rt.h"

void	parse_ambient(t_scene *scene, char *line, int i)
{
	check_one_amb(scene);
	scene->amb = (t_amb *)malloc(sizeof(t_amb));
	ft_skip_space_tab(line, &i);
	scene->amb->ratio = parse_light_ratio(line, &i);
	check_if_missing_space(line, i);
	ft_skip_space_tab(line, &i);
	set_color_rgb(&scene->amb->color, line, &i);
	ft_skip_space_tab(line, &i);
	check_surplus_info(scene, line, i);
}

	// printf("AMBIANT RATIO = %f\n", scene->amb->ratio);
	// printf("RED VALUE = %d\n", scene->amb->color.r);
	// printf("GREN VALUE = %d\n", scene->amb->color.g);
	// printf("BLUE VALUE = %d\n", scene->amb->color.b);
void	parse_camera(t_scene *scene, char *line, int i)
{
	check_one_cam(scene);
	scene->cam = (t_cam *)malloc(sizeof(t_cam));
	ft_skip_space_tab(line, &i);
	set_coord_xyz(&scene->cam->origin, line, &i);
	check_if_missing_space(line, i);
	ft_skip_space_tab(line, &i);
	set_coord_xyz(&scene->cam->dir, line, &i);
	check_unit_range(&scene->cam->dir);
	check_if_missing_space(line, i);
	ft_skip_space_tab(line, &i);
	scene->cam->fov = parse_field_of_view(line, &i);
	ft_skip_space_tab(line, &i);
	check_surplus_info(scene, line, i);
}

void	parse_light(t_scene *scene, char *line, int i)
{
	check_one_lit(scene);
	scene->lit = (t_lit *)malloc(sizeof(t_lit));
	ft_skip_space_tab(line, &i);
	set_coord_xyz(&scene->lit->origin, line, &i);
	check_if_missing_space(line, i);
	ft_skip_space_tab(line, &i);
	scene->lit->ratio = parse_light_ratio(line, &i);
	scene->lit->color.r = 255;
	scene->lit->color.g = 255;
	scene->lit->color.b = 255;
	ft_skip_space_tab(line, &i);
	check_surplus_info(scene, line, i);
}
