
#include "../incls/mini_rt.h"
#include "../libft/libsrcs/libft.h"
#include "../libft/libsrcs/ft_printf.h"
#include "../libft/libsrcs/get_next_line.h"
#include "../minilibx_opengl/mlx.h"

#include <stdio.h>

// t_vec3 rotate_dir(t_vec3 direction, t_scene *scene)
// {
// 	double x;
// 	double y;
// 	double z;
// 	double	a;

// 	a = 0;
// 	x = direction.x * cos(a) - direction.z * sin(a);
// 	z = direction.x	* sin(a) + direction.z * cos(a);
// 	direction = vec_normalize(new_vector(x, direction.y, z));
// 	x = direction.x * cos(a) - direction.y * sin(a);
// 	z = direction.x	* sin(a) + direction.y * cos(a);
// 	direction = vec_normalize(new_vector(x, y, direction.z));
// 	return (direction);

// }


t_vec3	get_ray_dir(t_scene *scene, t_mlx *mlx, int x, int y, t_vec3 cam_norm)
{
	t_vec3	direction;
	
	direction.x = y - mlx->width / 2;
	direction.y = mlx->height / 2 - x;
	direction.z = - mlx->width / (2 * tan(scene->cam->fov * M_PI / 360));
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
			dir = get_ray_dir(scene, mlx, x, y, vec_normalize(scene->cam->dir));
			//dir = rotate_dir(dir, scene);
			color = intersection(scene, dir); //faire une struct obj ou ou tab döbj
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
	hook_collection(mlx, scene);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	mlx_loop(mlx->mlx);
}



int main (int argc, char **argv)
{
	t_scene *scene;

	if (argc != 2)
		return(-100);
	scene = ft_calloc(1, sizeof(t_scene);
	init_scene(scene);
	parse_machine(scene, argv[1]);
	make_scene(scene);
    return (0);
}