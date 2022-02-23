#include "../../incls/mini_rt.h"

int	parse_sphere(t_scene *scene, char *line, int i)
{
	t_shape *new;
    t_sphere *sp;

    new = ft_calloc(1, sizeof(t_shape));
    sp = ft_calloc(1, sizeof(t_sphere));
	ft_skip_space_tab(line, &i);
	set_coord_xyz(&sp->center, line, &i);
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
    vector_add_back_element(scene->shape, (void *)new);

	// vector_add_back_element(scene->shape, (void *)new);
	// vector_add_back_element(scene->shape, (void *)new);
	// vector_add_back_element(scene->shape, (void *)new);
	// vector_add_back_element(scene->shape, (void *)new);
	// vector_add_back_element(scene->shape, (void *)new);

	// while (scene->shape->total > 0)
	// {
	// 	printf("nb of shapes in the vector array = %zu\n", scene->shape->total);
	// 	printf("object type  %d\n", ((t_shape *)scene->shape->elements[0])->type);
	// 	printf("sphere %d\n", ((t_sphere *)((t_shape *)scene->shape->elements[0])->shape)->color.r);
	// 	printf("sphere %d\n", ((t_sphere *)((t_shape *)scene->shape->elements[0])->shape)->color.g);
	// 	printf("sphere %d\n", ((t_sphere *)((t_shape *)scene->shape->elements[0])->shape)->color.b);
	// 	scene->shape->total--;
	// }
	return (0);
}



int	parse_plane(t_scene *scene, char *line, int i)
{
	t_shape *new;
    t_plane *pl;

    new = ft_calloc(1, sizeof(t_shape));
    pl = ft_calloc(1, sizeof(t_plane));

	ft_skip_space_tab(line, &i);
	set_coord_xyz(&pl->center, line, &i);

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
    vector_add_back_element(scene->shape, (void *)new);

	return (0);
}


int	parse_cylinder(t_scene *scene, char *line, int i)
{
	t_shape *new;
    t_cylinder *cy;

    new = ft_calloc(1, sizeof(t_shape));
    cy = ft_calloc(1, sizeof(t_cylinder));

	ft_skip_space_tab(line, &i);
	set_coord_xyz(&cy->center, line, &i);

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
    vector_add_back_element(scene->shape, (void *)new);

	return (0);
}
