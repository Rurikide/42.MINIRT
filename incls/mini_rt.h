/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadia <jbadia@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 20:00:37 by tshimoda          #+#    #+#             */
/*   Updated: 2022/02/16 15:30:39 by jbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H

# include "color.h"
# include "parsing.h"
# include "scene.h"
# include "vector_3d.h"
# include "vector_array.h"


# include "../libft/libsrcs/libft.h"
# include "../libft/libsrcs/ft_printf.h"
# include "../libft/libsrcs/get_next_line.h"

# include "../minilibx_opengl/mlx.h"

# define KEY_ESC 53 //ESCAPE
# define KEY_Q 12 // Q

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*adr;
	int		width;
	int		height;
	int		init;
	int		bpp;
	int		endian;
	int		w_len;
}			t_mlx;

typedef struct s_rt
{
	t_mlx *mlx;
	int i;
}				t_rt;

t_mlx	*get_mlx(void);
void	init_rt(t_rt *rt);

int		key_event(int keycode, t_mlx *mlx);
int		click_close_window(void);
void	hook_collection(t_mlx *mlx);
void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);

#endif