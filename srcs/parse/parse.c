#include "../../incls/mini_rt.h"

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
	{
		printf("\vERROR LIGHT VALUE\v\n");
		return (-100);
	}
	*i = index + float_len;
	return (ratio);	
}

int	parse_field_of_view(t_scene *scene, char *line, int *i)
{
	int	index;
	int	fov_len;

	index = *i;
	fov_len = get_int_len(line, index);
	scene->cam->fov = ft_atoi(&line[index]);
	if (scene->cam->fov < 0 || scene->cam->fov > 180)
	{
		printf("\vERROR FOV VALUE\v\n");
		return (-100);
	}
	*i = index + fov_len;
	return (0);	
}

int	check_unit_range(double x, double y, double z)
{
	if (x < -1.0 || x  > 1.0)
	{
		printf("\vERROR UNIT DIR X \v\n");
		return (-1);
	}
	if (y < -1.0 || y  > 1.0)
	{
		printf("\vERROR UNIT DIR Y\v\n");
		return (-1);
	}
	if (z < -1.0 || z  > 1.0)
	{
		printf("\vERROR UNIT DIR Z\v\n");
		return (-1);
	}
	return (0);
}

int	parse_3unit_ratio(t_scene *scene, char *line, int *i)
{
	int	unit_len;
	int	index;

	index = *i;
	unit_len = get_float_len(line, index);
	scene->cam->dir.x = ft_atod(&line[index]);
	if (line[index + unit_len] != ',')
		return (-1);
	else
		index += unit_len + 1;
	unit_len = get_float_len(line, index);
	scene->cam->dir.y = ft_atod(&line[index]);
	if (line[index + unit_len] != ',')
		return (-1);
	else
		index += unit_len + 1;
	unit_len = get_float_len(line, index);
	scene->cam->dir.z = ft_atod(&line[index]);
	*i = index + unit_len;
	// check_unit_range(scene);
	return (0);
}

int	check_rgb_range(int r, int g, int b)
{
	if (r < 0 || r  > 255)
	{
		printf("\vERROR RED VALUE \v\n");
		return (-1);
	}
	if (g < 0 || g  > 255)
	{
		printf("\vERROR GREEN VALUE\v\n");
		return (-1);
	}
	if (b < 0 || b  > 255)
	{
		printf("\vERROR BLUE VALUE\v\n");
		return (-1);
	}
	return (0);
}

int	parse_3color_rgb(t_scene *scene, char *line, int *i)
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
	// check_rgb_range(scene);
	return (0);
}

int	parse_1color_rgb(char *line, int *i)
{
	int	rgb_len;
	int	value;
	int	index;

	index = *i;

	if (!ft_isdigit(line[index]))
	{
		printf("parse1color, not a digit\n");
		return (-1000);
	}
	rgb_len = get_int_len(line, index);
	value = ft_atoi(&line[index]);
	*i = index + rgb_len;
	return (value);
}


int	parse_3coord_xyz(t_scene *scene, char *line, int *i)
{
	int	coord_len;
	int	index;

	index = *i;
	coord_len = get_float_len(line, index);
	scene->cam->origin.x = ft_atod(&line[index]);
	if (line[index + coord_len] != ',')
		return (-1);
	else
		index += coord_len + 1;
	coord_len = get_float_len(line, index);
	scene->cam->origin.y = ft_atod(&line[index]);
	if (line[index + coord_len] != ',')
		return (-1);
	else
		index += coord_len + 1;
	coord_len = get_float_len(line, index);
	scene->cam->origin.z = ft_atod(&line[index]);
	*i = index + coord_len;
	// check window width heigth ???
	return (0);
}


int	parse_camera(t_scene *scene, char *line)
{
	int			i;

	if (scene->cam != NULL)
	{
		printf("IL Y A DEJA UNE CAMERA\n");
		return (-1);
	}
	scene->cam= (t_cam *)malloc(sizeof(t_cam));
	// on sait que line[0] == 'C', donc je mets i = 1;
	i = 1;
	while (ft_is_space_tab(line[i]))
		i++;
	parse_3coord_xyz(scene, line, &i);
	if (!ft_is_space_tab(line[i]))
		return (-1);
	while (ft_is_space_tab(line[i]))
		i++;
	parse_3unit_ratio(scene, line, &i);
	// printf("RED VALUE = %d\n", scene->amb->color.r);
	// printf("GREN VALUE = %d\n", scene->amb->color.g);
	// printf("BLUE VALUE = %d\n", scene->amb->color.b);
	while (ft_is_space_tab(line[i]))
		i++;

	// parse_fov(scene, line, &i);

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
	else if (line[0] == 'C' && ft_is_space_tab(line[1]))
		parse_camera(scene, line);
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
