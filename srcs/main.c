/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadia <jbadia@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 21:57:36 by tshimoda          #+#    #+#             */
/*   Updated: 2022/02/16 15:30:07 by jbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incls/mini_rt.h"
#include "../libft/libsrcs/libft.h"
#include "../libft/libsrcs/ft_printf.h"
#include "../libft/libsrcs/get_next_line.h"
#include "../minilibx_opengl/mlx.h"

#include <stdio.h>

int color_test(t_rt *rt)
{
	t_mlx	*mlx;
	t_rgb rgb;
	t_rgb	c2;
	int i;
	int	j;
	int color;
	int color2;

	rgb.r = 255;
	rgb.g = 0;
	rgb.b = 0;

	c2.r = 0;
	c2.g = 0;
	c2.b = 255;

	mlx = get_mlx();
	i = 0;
	color = add_color(rgb_to_int(rgb), rgb_to_int(c2));
	color2 = rgb_to_int(rgb) + rgb_to_int(c2);
	while (i < mlx->height)
	{
		j = 0;
		while (j < mlx->width)
		{
			my_mlx_pixel_put(mlx, j, i, color2);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	return (1);
}

int main (int argc, char **argv)
{
   	t_rt *m_rt;
   	t_mlx *mlx;
	
	mlx = get_mlx();
	m_rt = calloc(1, sizeof(t_rt));
	init_rt(m_rt);
	hook_collection(mlx);
	mlx_loop_hook(mlx->mlx, color_test, m_rt);
	mlx_loop(mlx->mlx);

    
    return (0);
}