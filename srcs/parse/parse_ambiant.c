#include "../../incls/mini_rt.h"

int	parse_ambient(t_scene *scene, char *line)
{
	int			i;

	if (scene->amb != NULL)
	{
		printf("IL Y A DEJA UNE AMBIANT LIGHT\n");
		return (-1);
	}
	scene->amb = (t_amb *)malloc(sizeof(t_amb));
	i = 1;
	
	ft_skip_space_tab(line, &i);


	scene->amb->ratio = parse_light_ratio(line, &i);
	if (!ft_is_space_tab(line[i]))
		return (-1);


	ft_skip_space_tab(line, &i);

	scene->amb->color.r = parse_1color_rgb(line, &i);
	if (line[i] != ',')
	{
		printf("not a virgule\n");
		return (-1);
	}
	i++;
	scene->amb->color.g = parse_1color_rgb(line, &i);
	if (line[i] != ',')
	{
		printf("not a virgule\n");
		return (-1);
	}
	i++;
	scene->amb->color.b = parse_1color_rgb(line, &i);

	printf("AMBIANT RATIO = %f\n", scene->amb->ratio);
	printf("RED VALUE = %d\n", scene->amb->color.r);
	printf("GREN VALUE = %d\n", scene->amb->color.g);
	printf("BLUE VALUE = %d\n", scene->amb->color.b);
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