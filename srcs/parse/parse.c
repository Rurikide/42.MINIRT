/*
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
	double ratio;
	int	index;
	int	float_len;

	index = *i;
	ratio = 0;
	float_len = get_float_len(line, index);
	ratio = ft_atod(&line[index]);
	if (ratio < 0.0 || ratio > 1.0)
		return (-1);	
	*i = index + float_len;
	return (ratio);	
}

int	get_int_len(char *line, int i)
{
	int int_len;

	int_len = 0;
	if (ft_isdigit(line[i]))
	{
		while (ft_isdigit(line[i]))
		{
			i++;
			int_len++;
		}
	}
	else
	{
		printf("extra space or non-digit after virgule\n");
		return (-100);
	}
	return (int_len);
}

int	parse_color_rgb(t_scene *scene, char *line, int *i)
{
	int	rgb_len;
	int	index;

	index = *i;
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
	*i = index + rgb_len;
	if (scene->amb->color.r < 0 || scene->amb->color.r  > 255)
	{
		printf("\vERROR RED VALUE \v\n");
		return (-1);
	}
	if (scene->amb->color.g < 0 || scene->amb->color.g  > 255)
	{
		printf("\vERROR GREEN VALUE\v\n");
		return (-1);
	}
	if (scene->amb->color.b < 0 || scene->amb->color.b  > 255)
	{
		printf("\vERROR BLUE VALUE\v\n");
		return (-1);
	}
	return (0);
}

int	parse_ambient(t_scene *scene, char *line)
{
	int			i;

	if (scene->amb != NULL)
	{
		printf("IL Y A DEJA UNE AMBIANT LIGHT\n");
		return (-1);
	}
	scene->amb = (t_amb *)malloc(sizeof(t_amb));
	// on sait que line[0] == 'A', donc je mets i = 1;
	i = 1;
	while (ft_is_space_tab(line[i]))
		i++;
	scene->amb->ratio = parse_light_ratio(line, &i);

	if (!ft_is_space_tab(line[i]))
		return (-1);
	while (ft_is_space_tab(line[i]))
		i++;
	parse_color_rgb(scene, line, &i);
	// printf("RED VALUE = %d\n", scene->amb->color.r);
	// printf("GREN VALUE = %d\n", scene->amb->color.g);
	// printf("BLUE VALUE = %d\n", scene->amb->color.b);
	while (ft_is_space_tab(line[i]))
		i++;
	if (line[i] != '\n' && line[i] != '\0')
	{
		printf("ERROR TOO MANY INFO\n");
		printf("FOUND %c\n", line[i]);
		return (-1);
	}
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
	// // check si l'extension est .rt et si le fichier existe. return -1 en cas d'erreur
	check_rt_file(file);

	// // ft_read effectue open, GNL pour récupérer une ligne à la fois et ensuite appelle d'autres fonctions pour parser
	// // note la fonction check_rt_file verifie déjà si le open fd est valide. 
	gnl_preparsing(scene, file); 
	
	return ;
}

*/