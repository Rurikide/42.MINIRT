/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 15:10:51 by tshimoda          #+#    #+#             */
/*   Updated: 2022/02/19 17:03:25 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incls/mini_rt.h"
#include "../../incls/parsing.h"

void	parse_ambient(t_scene *scene, char *line)
{
	static int	ambiant_on;
	int			i;

	i = 1;
	tab = NULL;
	if (ambiant_on == NULL)
	{
		
	}
	else
		return (-1);
	// On retourne une erreur si ambiant_on != NULL car cela signifie qu'on a déja parsé une lumiere ambiante
}





int	check_parsing_type(t_scene *scene, char *line)
{
	if (ft_is_space_tab(line[0]))
		return (-1);
	if (line[0] == 'A' && ft_is_space_tab(line[1]))
		parse_ambient(scene, line);
	else if (line[0] == 'C' && ft_is_space_tab(line[1]))
		parse_camera(scene, line);
	else if (line[0] == 'L' && ft_is_space_tab(line[1]))
		parse_light(scene, line);
	else if (line[0] == 's' && line[1] == 'p' && ft_is_space_tab(line[2]))
		parse_sphere(scene, line);
	else if (line[0] == 'p' && line[1] == 'l' && ft_is_space_tab(line[2]))
		parse_plane(scene, line);
	else if (line[0] == 'c' && line[1] == 'y' && ft_is_space_tab(line[2]))
		parse_cylinder(scene, line);
	return (0);
}

int	ft_is_space_tab(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
	// return message à faire
}

int	check_valid_ascii(char *line)
{
	char	*set;
	int		i;
	int		j;
	int		valid;

	set = (char [16]){9, 10, 11, 12, 13, 44, 46, 65, 67, 76, 99, 108, 112, 116, 121};
	i = 0;
	while (line[i])
	{
		valid = 0;
		j = 0;
		while (set[j])
		{
			if (line[i] == set[j])
				valid = 1;
			j++;
		}
		if (valid == 0)
			return (-1);
		i++;
	}
	return (valid);
}

int	gnl_preparsing(t_scene *scene, char *file)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (check_valid_ascii(line) == -1)
		{
			free(line);
			return (-1);
			//message d'erreur;
		}
		check_parsing_type(scene, line);
		free(line);
	}
	return (0);
}

int	check_rt_file(char *file)
{
	int		fd;
	int		len;
	int		v_len;
	char	*valid;

	fd = 0;
	v_len = 2;
	valid = ".rt";
	len = ft_strlen(file) - 1;
	while (valid[v_len])
	{
		if (len < 1 || valid[v_len] != file[len])
			return (-1);
		v_len--;
		len--;
	}
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (-1);
	close (fd);
	return (1);
}

void	free_scene_exit(t_scene *scene)
{
	if (scene->amb != NULL)
		free(scene->amb);
	if (scene->cam != NULL)
		free(scene->cam);
   	if (scene->light != NULL)
		free(scene->light);
	if (scene->sp != NULL)
		free(scene->sp);
	if (scene->pl != NULL)
		free(scene->pl);	
	if (scene->cy != NULL)
		free(scene->cy);
	free(scene);
	exit(0);
}

int	init_scene(t_scene *scene)
{
	scene = calloc(1, sizeof(t_scene));
	if (!scene)
		return (-1); 
	scene->amb = NULL;
    scene->cam = NULL;
    scene->light = NULL;
	scene->sp = NULL;
	scene->pl = NULL;
	scene->cy = NULL;
	return (0);
}
 
void	parse_machine(t_scene *scene, char *file)
{
	// check si l'extension est .rt et si le fichier existe. return -1 en cas d'erreur
	// error message : Invalid .rt file OU Error opening file
	check_rt_file(file);
	// 
	// ft_read effectue open, GNL pour récupérer une ligne à la fois et ensuite appelle d'autres fonctions pour parser
	// note la fonction check_rt_file verifie déjà si le open fd est valide. 
	gnl_preparsing(scene, file); 
	// check_valid_ascii, check_parsing_type;
	// DANS LE gnl_parsing, on appelle check_parsing_type et selon le identifier (A, C, L, et), on parse line avec la bonne fonction de parsing.

	return ;
}

// int	PSEUDO_MAIN(int ac, char **av)
// {
// 	t_scene *scene;

//	init(scene);
// 	if (ac == 2)
// 		parse_machine(scene, av[1]);
// 	return (0);
// }