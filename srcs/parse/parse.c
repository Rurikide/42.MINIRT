/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 15:10:51 by tshimoda          #+#    #+#             */
/*   Updated: 2022/02/17 15:10:59 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incls/mini_rt.h"
#include "../../incls/parsing.h"

/*
DANS LE INT MAIN
{
typedef struct T_SCENE
    t_amb	    *amb;
    t_cam       *cam;
    t_lit       *light;
	t_sphere	*sp;
	t_plan	    *pl;
	t_cy	    *cy;
}
*/

// FOLLOWING IS PSEUDO CODE 
void    parse_machine(t_parse *data, char *file)
{
	//step 1 : vérifier que c'est un fichier .rt et qu'il est valide
	ft_is_valid_file(file)
	//step 2 : utiliser GNL et parser ligne par ligne et remplir la struct t_parse data
	ft_read_file(data, file)
	//step 3 : vérifier si AMBIENT, CAMERA, LIGHT sont null

}

int    ft_is_valid_file(char *file)
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
			return(print_error_free_exit(err_nb));
		v_len--;
		len--;
	}
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return(print_error_free_exit(err_nb));
	close (fd);
	return (1);
}

void    ft_read_file(t_parse *data, char *file)
{
		int fd;
		char *line;

		fd = open(file, O_RDONLY);
		// déjà vêrifié si le fd file est valide dans la fonction ft_is_valid_file
		while (1)
		{
			line = get_next_line(fd);
			if (line == NULL)
				break ;
			ft_scan_line(data, line);
			free(line);
		}
}


void    ft_scan_line(t_parse *data, char *line)
{
	int i;

	i = 0;
	// faire une fonction qui liste les identifier valide ???
	
	if (line[0] == 'A' && ft_isspace(line[1]))
		parse_ambient(data, line);
	else if (line[0] == 'C' && ft_isspace(line[1]))
		parse_camera(data, line);
	else if (line[0] == 'L' && ft_isspace(line[1]))
		parse_light(data, line);
	else if (line[0] == 's' && line[1] == 'p' && ft_isspace(line[2]))
		parse_sphere(data, line);
	else if (line[0] == 'p' && line[1] == 'l' && ft_isspace(line[2]))
		parse_plane(data, line);
	else if (line[0] == 'c' && line[1] == 'y' && ft_isspace(line[2]))
		parse_cylinder(data, line);		
}

//WORK IN PROGRESS

//  If any misconfiguration of any kind is encountered in the file the program must exit properly and return "Error\n" followed by an explicit error message of your choice.

void parse_ambient(t_parse *data, char *line)
{
    // on sait que line[0] == 'A' et line[1] == ' ' 
    static int ambiant_on;
	char **tab;
	int i = 1;
	tab = NULL;
    if (ambiant_on == NULL)
    {
		ambiant_on = 1;
    	tab = ft_split(line, ' ');
		while (ft_valid_char(line[i])
		{
			
		}
    }
    else
        return (error);
}

int	ft_valid_char(char *line)
{
	int i = 0;

	while (line[i])
	{
		if (!ft_isspace(line[i]) || !ft_isalnum(line[i]))
			return(-1);
		i++;
	}
	return(1);
}