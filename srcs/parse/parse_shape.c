/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shape.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 16:59:16 by tshimoda          #+#    #+#             */
/*   Updated: 2022/03/18 16:59:18 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incls/mini_rt.h"

void	parse_sphere(t_scene *scene, char *line, int i)
{
	t_shape	*new;
	t_sp	*sp;

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
	new->shape = (void *)sp;
	new->type = SP;
	new->origin = sp->origin;
	new->dir = new_vector(0, 0, 0);
	new->color = sp->color;
	vector_add_back_element(scene->objs, (void *)new);
}

void	parse_cylinder(t_scene *scene, char *line, int i)
{
	t_shape	*new;
	t_cy	*cy;

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
	parse_cylinder2(new, cy);
	vector_add_back_element(scene->objs, (void *)new);
}

void	parse_cylinder2(t_shape *new, t_cy *cy)
{
	new->shape = (void *)cy;
	new->type = CY;
	new->origin = cy->origin;
	new->dir = cy->dir;
	new->color = cy->color;
}

void	parse_plane(t_scene *scene, char *line, int i)
{
	t_shape	*new;
	t_pl	*pl;

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
	new->shape = (void *)pl;
	new->type = PL;
	new->origin = pl->origin;
	new->dir = pl->dir;
	new->color = pl->color;
	vector_add_back_element(scene->objs, (void *)new);
}
