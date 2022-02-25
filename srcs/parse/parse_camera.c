#include "../../incls/mini_rt.h"

int	parse_camera(t_scene *scene, char *line, int i)
{
	check_one_cam(scene);
	scene->cam = (t_cam *)malloc(sizeof(t_cam));
	ft_skip_space_tab(line, &i);
	set_coord_xyz(&scene->cam->origin, line, &i);
	check_if_missing_space(line, i);
	ft_skip_space_tab(line, &i);
	set_coord_xyz(&scene->cam->dir, line, &i);

	check_unit_range(&scene->cam->dir);
	
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
	check_surplus_info(scene, line, i);
	return (0);
}