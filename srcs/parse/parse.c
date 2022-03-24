/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 15:22:35 by tshimoda          #+#    #+#             */
/*   Updated: 2022/03/17 15:20:45 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incls/mini_rt.h"

int	check_parsing_type(t_scene *scene, char *line)
{
	if (line[0] == 'A' && ft_is_space_tab(line[1]))
		parse_ambient(scene, line, 1);
	else if (line[0] == 'C' && ft_is_space_tab(line[1]))
		parse_camera(scene, line, 1);
	else if (line[0] == 'L' && ft_is_space_tab(line[1]))
		parse_light(scene, line, 1);
	else if (line[0] == 's' && line[1] == 'p' && ft_is_space_tab(line[2]))
		parse_sphere(scene, line, 2);
	else if (line[0] == 'p' && line[1] == 'l' && ft_is_space_tab(line[2]))
		parse_plane(scene, line, 2);
	else if (line[0] == 'c' && line[1] == 'y' && ft_is_space_tab(line[2]))
		parse_cylinder(scene, line, 2);
	else if (line[0] == '\n')
		return (0);
	else
		print_error_exit(scene, \
		"Line must begin with key identifier, followed by a space");
	return (0);
}

int	gnl_preparsing(t_scene *scene, char *file)
{
	int		fd;
	int		error;
	char	*line;

	error = 0;
	fd = open(file, O_RDONLY);
	while (error == 0)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		error = check_valid_ascii(scene, line, 0, 0);
		if (error == 1)
			error = check_parsing_type(scene, line);
		free(line);
	}
	close(fd);
	return (error);
}

void	parse_machine(t_scene *scene, char *file)
{
	if (check_rt_file(file) == -1)
		print_error_exit(scene, "invalid rt file");
	gnl_preparsing(scene, file);
	check_amb_cam_lit(scene);
}
