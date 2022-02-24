#include "../../incls/mini_rt.h"

int	parse_light(t_scene *scene, char *line, int i)
{
	check_one_lit(scene);
	scene->lit = (t_lit *)malloc(sizeof(t_lit));
	//LUMIERE BLANCHE
	scene->lit->color.r = 255;
	scene->lit->color.g = 255;
	scene->lit->color.b = 255;
	ft_skip_space_tab(line, &i);
	set_coord_xyz(&scene->lit->origin, line, &i);
	// scene->lit->origin.x = parse_1coord_xyz(line, &i);
	// check_if_missing_comma(line, &i);
	// scene->lit->origin.y = parse_1coord_xyz(line, &i);
	// check_if_missing_comma(line, &i);
	// scene->lit->origin.z = parse_1coord_xyz(line, &i);
	check_if_missing_space(line, i);
	ft_skip_space_tab(line, &i);
    scene->lit->ratio = parse_light_ratio(line, &i);
    // BONUS couleur des spotlits
    // check_if_missing_space(line, i);
	// ft_skip_space_tab(line, &i);
	// scene->lit->color.r = parse_1color_rgb(line, &i);
	// check_if_missing_comma(line, &i);
	// scene->lit->color.g = parse_1color_rgb(line, &i);
	// check_if_missing_comma(line, &i);
	// scene->lit->color.b = parse_1color_rgb(line, &i);
	// printf("lit origin x = %f\n", scene->lit->origin.x);
	// printf("lit origin y = %f\n", scene->lit->origin.y);
	// printf("lit origin z = %f\n", scene->lit->origin.z);

	// printf("lit ratio  x = %f\n", scene->lit->ratio);

	// printf("lit RED VALUE = %d\n", scene->lit->color.r);
	// printf("lit GREEN VALUE = %d\n", scene->lit->color.g);
	// printf("lit BLUE VALUE = %d\n", scene->lit->color.b);

	ft_skip_space_tab(line, &i);
	check_surplus_info(scene, line, i);
	return (0);
}
