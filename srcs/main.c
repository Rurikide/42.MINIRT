

#include "../incls/mini_rt.h"
#include "../libft/libsrcs/libft.h"
#include "../libft/libsrcs/ft_printf.h"
#include "../libft/libsrcs/get_next_line.h"
#include "../minilibx_opengl/mlx.h"

#include <stdio.h>

// t_vec3	add_3_vec(t_vec3 a, t_vec3 b, t_vec3 c)
// {
// 	t_vec3 resultante;

// 	resultante.x = a.x + b.x + c.x;
// 	resultante.y = a.y + b.y + c.y;
// 	resultante.z = a.z + b.z + c.z;
// 	return (resultante);
// }

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

// t_vec3	get_ray_dir(t_scene *scene, t_mlx *mlx, int x, int y, t_vec3 cam_norm)
// {
// 	double	fov;
// 	t_vec3	direction;
// 	t_vec3	a;
// 	t_vec3	b;
// 	t_vec3	c;

// 	fov = mlx->width / (2 * tanf(scene->cam->fov * M_PI / 180));
// 	a = new_vector(fov, y - mlx->width / 2, -(x - mlx->height / 2));
// 	b = new_vector(- (y - mlx->width /2), fov, -(x - mlx->height / 2));
// 	c = new_vector(-(x - mlx->height / 2), y - mlx->width /2, fov);
// 	direction = add_3_vec(vec_multiply(a, cam_norm.x), 
// 		vec_multiply(b, cam_norm.y), vec_multiply(c, cam_norm.z));
// 	return(direction);
// }

// void	ray_tracing(t_scene *scene)
// {
// 	int	x;
// 	int	y;
// 	int	color;
// 	t_mlx	*mlx;
// 	t_vec3	dir;
	
// 	x = 0;
// 	mlx = get_mlx();
// 	while(x < mlx->height)
// 	{
// 		y = 0;
// 		while (y < mlx->width)
// 		{
// 			dir = get_ray_dir(scene, mlx, x, y, vec_normalize(scene->cam->dir));
// 			dir = rotate_dir(dir, scene);
// 			color = intersection(scene, dir); //faire une struct obj ou ou tab döbj
// 			my_mlx_pixel_put(mlx, y, x, color);
// 			y++;
// 		}
// 		x++;
// 	}
// }

// void	make_scene(t_scene *scene)
// {
// 	t_mlx *mlx;

// 	mlx = get_mlx();
// 	ray_tracing(scene);
// 	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
// 	hook_collection(mlx);
// 	mlx_loop(mlx->mlx);
// }

int main (int argc, char **argv)
{
	t_scene *scene;
	// t_mlx	*mlx;
	// t_rt 	*m_rt; 

	if (argc != 2)
		return(-100);
	scene = (t_scene *)malloc(sizeof(t_scene));
	init_scene(scene);
	parse_machine(scene, argv[1]);
	
	// mlx = get_mlx();
	// m_rt = calloc(1, sizeof(t_rt));
	// init_rt(m_rt);
	// make_scene(m_rt->scene);
	// if (argc != 2)
	// 	return (-1);

	// printf("%d\n", scene->amb->color.r);
    return (0);
}