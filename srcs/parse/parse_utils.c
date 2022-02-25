#include "../../incls/mini_rt.h"

int	check_valid_ascii(t_scene *sc, char *line, int i, int j)
{
	char	*charset;
	char	*numbers;
	char	*wspaces;
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
			print_error_exit(sc, "Found invalid character");
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
	if (scene->amb == NULL || scene->cam == NULL)
		print_error_exit(scene, "Missing Ambiant or Camera");
	return (0);
}

int	check_one_amb(t_scene *scene)
{
	if (scene->amb != NULL)
		print_error_exit(scene, "Max one Ambiant light [A]");
	return (0);
}

int	check_one_cam(t_scene *scene)
{
	if (scene->cam != NULL)
		print_error_exit(scene, "Max one Camera [C]");
	return (0);
}

int	check_one_lit(t_scene *scene)
{
	if (scene->lit != NULL)
		print_error_exit(scene, "Max one Light source [L]");
	return (0);
}

int	check_surplus_info(t_scene *scene, char *line, int i)
{
	if (ft_isalnum(line[i]) || ft_is_dash_comma_dot(line[i]))
		print_error_exit(scene, "Too many input for an element");
	return (0);
}

void	print_error_exit(t_scene *scene, char *msg)
{
	ft_putendl_fd("Error", 1);
	ft_putendl_fd(msg, 1);
	if (scene != NULL)
		free_scene(scene);
	exit(EXIT_FAILURE);
}
