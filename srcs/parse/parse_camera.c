#include "../../incls/mini_rt.h"

int	parse_camera(t_scene *scene, char *line, int i)
{
	if (scene->cam != NULL)
	{
		printf("IL Y A DEJA UNE CAMERA\n");
		return (-1);
	}
	scene->cam = (t_cam *)malloc(sizeof(t_cam));
	ft_skip_space_tab(line, &i);

	scene->cam->origin.x = parse_1coord_xyz(line, &i);
	check_if_missing_comma(line, &i);
	scene->cam->origin.y = parse_1coord_xyz(line, &i);
	check_if_missing_comma(line, &i);
	scene->cam->origin.z = parse_1coord_xyz(line, &i);
	
	check_if_missing_space(line, i);
	ft_skip_space_tab(line, &i);
	
	scene->cam->dir.x = parse_1coord_xyz(line, &i);
	check_if_missing_comma(line, &i);
	scene->cam->dir.y = parse_1coord_xyz(line, &i);
	check_if_missing_comma(line, &i);
	scene->cam->dir.z = parse_1coord_xyz(line, &i);
	
	check_if_missing_space(line, i);
	ft_skip_space_tab(line, &i);

	scene->cam->fov = parse_field_of_view(line, &i);


	printf("CAM origin x = %f\n", scene->cam->origin.x);
	printf("CAM origin y = %f\n", scene->cam->origin.y);
	printf("CAM origin z = %f\n", scene->cam->origin.z);


	printf("CAM dir x = %f\n", scene->cam->dir.x);
	printf("CAM dir y = %f\n", scene->cam->dir.y);
	printf("CAM dir z = %f\n", scene->cam->dir.z);

	printf("CAM field of view = %d\n", scene->cam->fov);

	ft_skip_space_tab(line, &i);
	if (ft_isalnum(line[i]))
	{
		printf("ERROR TOO MANY INFO\n");
		printf("FOUND %c\n", line[i]);
		return (-1);
	}
	return (0);
}
