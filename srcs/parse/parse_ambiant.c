#include "../../incls/mini_rt.h"

int	parse_ambient(t_scene *scene, char *line, int i)
{
	check_one_amb(scene);
	scene->amb = (t_amb *)malloc(sizeof(t_amb));
	ft_skip_space_tab(line, &i);
	scene->amb->ratio = parse_light_ratio(line, &i);
	check_if_missing_space(line, i);
	ft_skip_space_tab(line, &i);
	set_color_rgb(&scene->amb->color, line, &i);
	printf("AMBIANT RATIO = %f\n", scene->amb->ratio);
	printf("RED VALUE = %d\n", scene->amb->color.r);
	printf("GREN VALUE = %d\n", scene->amb->color.g);
	printf("BLUE VALUE = %d\n", scene->amb->color.b);
	ft_skip_space_tab(line, &i);
	check_surplus_info(scene, line, i);
	return (0);
}