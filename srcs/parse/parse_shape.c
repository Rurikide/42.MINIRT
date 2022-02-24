#include "../../incls/mini_rt.h"

void	parse_sphere(t_scene *scene, char *line, int i)
{
	t_shape *new;
    t_sp *sp;

    new = ft_calloc(1, sizeof(t_shape));
    sp = ft_calloc(1, sizeof(t_sp));
	new->hit_obj = &hit_sphere;
	ft_skip_space_tab(line, &i);
	set_coord_xyz(&sp->origin, line, &i);
	check_if_missing_space(line, i);
	ft_skip_space_tab(line, &i);
	sp->rad = parse_dimension(line, &i) / 2;
	check_if_missing_space(line, i);
	ft_skip_space_tab(line, &i);
	set_color_rgb(&sp->color, line, &i);
	ft_skip_space_tab(line, &i);
	check_surplus_info(scene, line, i);
	new->shape = (void*)sp;
    new->type = SP;
    vector_add_back_element(scene->objs, (void *)new);
}

void	parse_cylinder(t_scene *scene, char *line, int i)
{
	t_shape *new;
    t_cy *cy;

    new = ft_calloc(1, sizeof(t_shape));
    cy = ft_calloc(1, sizeof(t_cy));
	new->hit_obj = &hit_cylinder;
	ft_skip_space_tab(line, &i);
	set_coord_xyz(&cy->origin, line, &i);
	check_if_missing_space(line, i);
	ft_skip_space_tab(line, &i);
	set_coord_xyz(&cy->dir, line, &i);
	check_unit_range(&cy->dir);
	check_if_missing_space(line, i);
	ft_skip_space_tab(line, &i);
	cy->rad = parse_dimension(line, &i) / 2;
	check_if_missing_space(line, i);
	ft_skip_space_tab(line, &i);
	cy->height = parse_dimension(line, &i);
	check_if_missing_space(line, i);
	ft_skip_space_tab(line, &i);
	set_color_rgb(&cy->color, line, &i);
	ft_skip_space_tab(line, &i);
	check_surplus_info(scene, line, i);
	new->shape = (void*)cy;
    new->type = CY;
    vector_add_back_element(scene->objs, (void *)new);
}

void	parse_plane(t_scene *scene, char *line, int i)
{
	t_shape *new;
    t_pl *pl;

    new = ft_calloc(1, sizeof(t_shape));
    pl = ft_calloc(1, sizeof(t_pl));
	new->hit_obj = &hit_plane;
	ft_skip_space_tab(line, &i);
	set_coord_xyz(&pl->origin, line, &i);
	check_if_missing_space(line, i);
	ft_skip_space_tab(line, &i);
	set_coord_xyz(&pl->dir, line, &i);
	check_unit_range(&pl->dir);
	check_if_missing_space(line, i);
	ft_skip_space_tab(line, &i);
	set_color_rgb(&pl->color, line, &i);
	ft_skip_space_tab(line, &i);
	check_surplus_info(scene, line, i);
	new->shape = (void*)pl;
    new->type = PL;
    vector_add_back_element(scene->objs, (void *)new);
}

	// while (scene->objs->total > 0)
	// {
	// 	printf("nb of shapes in the vector array = %zu\n", scene->objs->total);
	// 	printf("sphere %d\n", ((t_sp *)((t_shape *)scene->objs->elements[0])->shape)->color.r);
	// 	printf("sphere %d\n", ((t_sp *)((t_shape *)scene->objs->elements[0])->shape)->color.g);
	// 	printf("sphere %d\n", ((t_sp *)((t_shape *)scene->objs->elements[0])->shape)->color.b);
	// 	scene->objs->total--;
	// }
		// res = s2->hit_obj(s2->shape, cam, dir);
		// if (s2->type == 1)
        //     printf("object type  %d\n", s2->type);
	// t_shape *s2;
	// s2 = (t_shape *)scene->objs->elements[0];
	// if (s2->type == 1)
	// double res;
