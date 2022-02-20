/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadia <jbadia@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 21:57:36 by tshimoda          #+#    #+#             */
/*   Updated: 2022/02/20 18:44:34 by jbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incls/mini_rt.h"
#include "../libft/libsrcs/libft.h"
#include "../libft/libsrcs/ft_printf.h"
#include "../libft/libsrcs/get_next_line.h"
#include "../minilibx_opengl/mlx.h"

#include <stdio.h>

t_vec3	get_ray_dir(t_scene *scene, t_mlx *mlx, int x, int y)
{
	t_vec3	direction;
	double	fov;

	fov = scene->cam->fov * M_PI / 180;
	direction.x =  y - mlx->width / 2;
	direction.y = x - mlx->height / 2;
	direction.z = - mlx->width / (2 * tan(fov / 2));
	new_vector(direction.x, direction.y, direction.z);
	return(vec_normalize(direction));
}

void	ray_tracing(t_scene *scene)
{
	int	x;
	int	y;
	int	color;
	t_mlx	*mlx;
	t_vec3	dir;
	
	x = 0;
	mlx = get_mlx();
	while(x < mlx->height)
	{
		y = 0;
		while (y < mlx->width)
		{
			dir = get_ray_dir(scene, mlx, x, y);
			color = intersection(&scene->sp, dir, scene); //faire une struct obj ou ou tab döbj
			my_mlx_pixel_put(mlx, y, x, color);
			y++;
		}
		x++;
	}
}

void	make_scene(t_scene *scene)
{
	t_mlx *mlx;

	mlx = get_mlx();
	ray_tracing(scene);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	hook_collection(mlx);
	mlx_loop(mlx->mlx);
}

int main (int argc, char **argv)
{
   	t_rt *m_rt;
   	t_mlx *mlx;
	
	mlx = get_mlx();
	m_rt = calloc(1, sizeof(t_rt));
	init_rt(m_rt);
	make_scene(m_rt->scene);
	//check_args and error
	//parsing
	//if(!amb_light | !camera ! |light)
	//	exit_error

    
    return (0);
}