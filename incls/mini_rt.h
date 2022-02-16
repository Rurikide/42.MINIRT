/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 20:00:37 by tshimoda          #+#    #+#             */
/*   Updated: 2022/02/16 11:27:08 by tshimoda         ###   ########.fr       */
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
}	t_mlx;

# define KEY_ESC 53 //ESCAPE
# define KEY_Q 12 // Q

#endif