/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 21:57:36 by tshimoda          #+#    #+#             */
/*   Updated: 2022/02/21 17:33:06 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incls/mini_rt.h"
#include "../libft/libsrcs/libft.h"
#include "../libft/libsrcs/ft_printf.h"
#include "../libft/libsrcs/get_next_line.h"
#include "../minilibx_opengl/mlx.h"

#include <stdio.h>

// int color_test(t_rt *rt)
// {
// 	t_mlx	*mlx;
// 	t_rgb rgb;
// 	int i;
// 	int	j;
// 	int color;

// 	rgb.r = 255;
// 	rgb.g = 0;
// 	rgb.b = 0;

// 	mlx = get_mlx();
// 	i = 0;
// 	color = rgb_to_int(rgb);
// 	while (i < mlx->height)
// 	{
// 		j = 0;
// 		while (j < mlx->width)
// 		{
// 			my_mlx_pixel_put(mlx, j, i, color);
// 			j++;
// 			color--;
// 		}
// 		i++;
// 	}
// 	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
// 	return (1);
// }

// MAIN de Justine
// int main (int argc, char **argv)
// {
//    	t_rt *m_rt;
//    	t_mlx *mlx;
	
// 	mlx = get_mlx();
// 	m_rt = calloc(1, sizeof(t_rt));
// 	init_rt(m_rt);
// 	hook_collection(mlx);
// 	mlx_loop_hook(mlx->mlx, color_test, m_rt);
// 	mlx_loop(mlx->mlx);

    
//     return (0);
// }


int main (int argc, char **argv)
{
	t_scene *scene;

	scene = NULL;
	init_scene(scene);
	
	if (argc != 2)
		return (-1);

	parse_machine(scene, argv[1]);
	// printf("%d\n", scene->amb->color.r);
    return (0);
}