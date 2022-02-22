#include "../../incls/mini_rt.h"

int	parse_light(t_scene *scene, char *line, int i)
{
	if (scene->light != NULL)
	{
		printf("IL Y A DEJA UN SPOTLIGHT!\n");
		return (-1);
	}
	scene->light = (t_lit *)malloc(sizeof(t_lit));
	ft_skip_space_tab(line, &i);

	scene->light->origin.x = parse_1coord_xyz(line, &i);
	check_if_missing_comma(line, &i);
	scene->light->origin.y = parse_1coord_xyz(line, &i);
	check_if_missing_comma(line, &i);
	scene->light->origin.z = parse_1coord_xyz(line, &i);
	
	check_if_missing_space(line, i);
	ft_skip_space_tab(line, &i);

    scene->light->ratio = parse_field_of_view(line, &i);

    // BONUS couleur des spotlights
    // check_if_missing_space(line, i);
	// ft_skip_space_tab(line, &i);

	// scene->light->color.r = parse_1color_rgb(line, &i);
	// check_if_missing_comma(line, &i);
	// scene->light->color.g = parse_1color_rgb(line, &i);
	// check_if_missing_comma(line, &i);
	// scene->light->color.b = parse_1color_rgb(line, &i);
	


	printf("LIGHT origin x = %f\n", scene->light->origin.x);
	printf("LIGHT origin y = %f\n", scene->light->origin.y);
	printf("LIGHT origin z = %f\n", scene->light->origin.z);
	printf("LIGHT ratio  x = %f\n", scene->light->ratio);

	ft_skip_space_tab(line, &i);
	if (ft_isalnum(line[i]))
	{
		printf("ERROR TOO MANY INFO\n");
		printf("FOUND %c\n", line[i]);
		return (-1);
	}
	return (0);
}
