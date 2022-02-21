/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 15:10:51 by tshimoda          #+#    #+#             */
/*   Updated: 2022/02/21 17:58:59 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incls/mini_rt.h"

int	ft_table_len(char **tab)
{
	int len;

	len = 0;
	while (tab[len])
		len++;
	return (len);
}

int	get_float_len(char *line, int i)
{
	int float_len;
	int dot;

	dot = 0;
	float_len = 0;
	if (line[i] == '-')
	{
		i++;
		float_len++;
	}
	if (ft_isdigit(line[i]))
	{
		while (ft_isdigit(line[i]) || line[i] == '.')
		{
			if (line[i] == '.')
				dot++;
			i++;
			float_len++;
		}
	}
	else
		return (-1);
	if (dot > 1)
		return (-1);
	return(float_len);
}

double	parse_light_ratio(char *line, int *i)
{
	// positive ratio range is 0.0 to 1.0, donc line[i + 1] doit absolument être '.'
	double ratio;
	int	index;
	int	float_len;

	index = (int)i;
	ratio = 0;
	float_len = get_float_len(line, index);
	ratio = ft_atod(&line[index]);
	if (ratio < 0.0 || ratio > 1.0)
		return (-1);
	// apres avoir parser le double, je modifiel'indice i que je recois par addresse.
	*i += float_len;
	return (ratio);	
}

int	get_int_len(char *line, int i)
{
	int int_len;

	int_len = 0;
	// if (line[i] == '-')
	// {
	// 	i++;
	// 	int_len++;
	// }
	// on veut un nombre entier positif
	if (ft_isdigit(line[i]))
	{
		while (ft_isdigit(line[i]))
		{
			i++;
			int_len++;
		}
	}
	else
		return (-1);
	return (int_len);
}

int	parse_color_rgb(t_scene *scene, char *line, int *i)
{
	int	rgb_len;
	int	index;

	index = (int)i;

	rgb_len = get_int_len(line, index);

	scene->amb->color.r = ft_atoi(&line[index]);

	if (line[index + rgb_len] != ',')
		return (-1);
	else
		index += rgb_len + 1;

	rgb_len = get_int_len(line, index);
	scene->amb->color.g = ft_atoi(&line[index]);

	if (line[index + rgb_len] != ',')
		return (-1);
	else
		index += rgb_len + 1;

	rgb_len = get_int_len(line, index);
	scene->amb->color.b = ft_atoi(&line[index]);

	*i = (index + rgb_len);
	
	
	// tab_rgb = ft_split(&line[index], ',');
	// if (!tab_rgb)
	// 	return (-1);
	// tab_len = ft_table_len(tab_rgb);
	// if (tab_len != 3);
	// 	return (-1);
	// scene->amb->color.r = ft_atoi(tab_rgb[0]);
	// scene->amb->color.g = ft_atoi(tab_rgb[1]);
	// scene->amb->color.b = ft_atoi(tab_rgb[2]);
	return (0);
}

int	parse_ambient(t_scene *scene, char *line)
{
	int			i;

	scene->amb = calloc(1, sizeof(t_amb));
	printf("parse ambient HERE\n");
	
	// if (scene->amb != NULL)
	// {
	// 	printf("yoy yoyoyoyoyo \n");
	// 	return (-1);
	// }
	
	printf("before ambiant malloc\n");

	// scene->amb = calloc(1, sizeof(t_amb));
	

	
	// if (!scene->amb)
	// 	return (-1);

	printf("after ambiant malloc\n");
	
	// on sait que line[0] == 'A', donc je mets i = 1;
	i = 1;
	while (ft_is_space_tab(line[i]))
		i++;

	// ensuite dans l'ordre, on doit parser le ratio qui est un double.

	printf("before parse light ratio\n");

	scene->amb->ratio = parse_light_ratio(line, &i);

	printf("after parse light ratio\n");
	// ensuite verifier qu'il y a un space_tab apres le light ratio
	// l'indice i a été déplacé dans parse_light_ratio
	if (!ft_is_space_tab(line[i]))
		return (-1);
	while (ft_is_space_tab(line[i]))
		i++;
	parse_color_rgb(scene, line, &i);
	// il n'y a rien d'autre a parser pour scene->amb, donc si on trouve autre chose que '\0' c'est une erreur
	while (ft_isspace(line[i]))
		i++;
	if (line[i] != '\0')
		return (-1);
	return (0);
}

int	check_parsing_type(t_scene *scene, char *line)
{
	// int error = 0;
	if (line[0] == 'A' && ft_is_space_tab(line[1]))
		parse_ambient(scene, line);
	// else if (line[0] == 'C' && ft_is_space_tab(line[1]))
	// 	parse_camera(scene, line);
	// else if (line[0] == 'L' && ft_is_space_tab(line[1]))
	// 	parse_spotlight(scene, line);
	// else if (line[0] == 's' && line[1] == 'p' && ft_is_space_tab(line[2]))
	// 	parse_sphere(scene, line);
	// else if (line[0] == 'p' && line[1] == 'l' && ft_is_space_tab(line[2]))
	// 	parse_plane(scene, line);
	// else if (line[0] == 'c' && line[1] == 'y' && ft_is_space_tab(line[2]))
	// 	parse_cylinder(scene, line);
	else if (line[0] == '\n')
		return (0);
	else
		return (-1); // message derreur 
	return (0);
	// return (error);
}

int	ft_is_space_tab(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
	// return message à faire
}

// check_valid_ascii() vérifie que la ligne ne contient que les caractères valides dans le fichier .rt
// par exemple ascii 65 = 'A' et 9 = '\n' 
int	check_valid_ascii(char *line)
{
	char	*charset;
	char	*numbers;
	char	*wspaces;
	int		i;
	int		j;
	int		valid;

	charset = (char [10]){48, 65, 67, 76, 99, 108, 112, 116, 121};
	numbers = (char [10]){49, 50, 51, 52, 53, 54, 55, 56, 57};
	wspaces = (char [10]){9, 10, 11, 12, 13, 32, 44, 45, 46};
	i = 0;
	while (line[i])
	{
		valid = 0;
		j = 0;
		while (charset[j])
		{
			if (line[i] == charset[j] || line[i] == numbers[j] || line[i] == wspaces[j])
				valid = 1;
			j++;
		}
		if (valid == 0)
		{
			//
			printf("invalid ascii\n");
			return (-1);
		}
		i++;
	}
	return (valid);
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
		error = check_valid_ascii(line);

		//check parsing type renvoi 1 on success
		printf("check parsing type\n");
		if (error == 1)
			error = check_parsing_type(scene, line);
		free(line);
	}
	close(fd);
	return (error);
	// return (ft_err_msg(error));
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

	// scene->amb = calloc(1, sizeof(t_amb));
	// scene->cam = calloc(1, sizeof(t_cam));
	// scene->light = calloc(1, sizeof(t_lit));
	scene->cam = NULL;
	scene->light = NULL;
	scene->sp = NULL;
	scene->pl = NULL;
	scene->cy = NULL;
	return (0);
}
 
void	parse_machine(t_scene *scene, char *file)
{
	// // check si l'extension est .rt et si le fichier existe. return -1 en cas d'erreur
	check_rt_file(file);

	// // ft_read effectue open, GNL pour récupérer une ligne à la fois et ensuite appelle d'autres fonctions pour parser
	// // note la fonction check_rt_file verifie déjà si le open fd est valide. 
	printf("parse machine\n");
	gnl_preparsing(scene, file); 
	
	return ;
}
