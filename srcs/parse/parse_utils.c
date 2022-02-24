#include "../../incls/mini_rt.h"

int	ft_is_space_tab(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
	// return message à faire
}

void	ft_skip_space_tab(char *line, int *i)
{
	int move_forward;
	int	index;

	move_forward = 0;
	index = *i;
	while (ft_is_space_tab(line[index]))
	{
		index++;
		move_forward++;
	}
	*i += move_forward;
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

	charset = (char [10]){48, 65, 67, 76, 99, 108, 112, 115, 121};
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

int	check_amb_cam(t_scene *scene)
{
	if	(scene->amb == NULL || scene->cam == NULL)
	{
		printf("Il faut une ambiant light && une camera\n");
		return (-100);
	}
	return (0);
}

int	check_one_amb(t_scene *scene)
{
	if (scene->amb != NULL)
	{
		printf("IL Y A DEJA UNE AMBIANT LIGHT\n");
		return (-100);
	}
	return (0);
}

int	check_one_cam(t_scene *scene)
{
	if (scene->cam != NULL)
	{
		printf("IL Y A DEJA UNE CAMERA\n");
		return (-100);
	}
	return (0);
}

int	check_one_lit(t_scene *scene)
{
	if (scene->lit != NULL)
	{
		printf("IL Y A DEJA UNE LIGHT\n");
		return (-100);
	}
	return (0);
}

int	check_surplus_info(t_scene *scene, char *line, int i)
{
	(void)scene;
	
	if (ft_isalnum(line[i]) || line[i] == '.' || line[i] == ',' || line[i] == '-')
	{
		printf("ERROR TOO MANY INFO\n");
		printf("FOUND %c\n", line[i]);
		return (-100);
	}
	return (0);
}