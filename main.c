
#include "../incls/mini_rt.h"
#include "../libft/libsrcs/libft.h"
#include "../libft/libsrcs/ft_printf.h"
#include "../libft/libsrcs/get_next_line.h"
#include "../libx/mlx.h"

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

t_vec3	add_3_vec(t_vec3 u, t_vec3 v, t_vec3 w)
{
	t_vec3	resultante;

	resultante.x = u.x + v.x + w.x;
	resultante.y = u.y + v.y + w.y;
	resultante.z = u.z + v.z + w.z;
	return (resultante);
}

t_vec3	get_ray_dir(t_scene *scene, t_mlx *mlx, double u, double v)
{
	// t_vec3	direction;
	
	// direction.x = y - mlx->width / 2;
	// direction.y = mlx->height / 2 - x;
	// direction.z = - mlx->width / (2 * tan(scene->cam->fov * M_PI / 360));
	// return(vec_normalize(direction));
//---------------------------------------------------------------
  	t_vec3 screen_center;
	t_vec3	cam_left_top;
	t_vec3	cam_right_top;
 	t_vec3	cam_bottom_left;
	t_vec3 point_on_screen;

 	screen_center = vec_add(scene->cam->origin, vec_multiply(scene->cam->dir, 1));
	cam_left_top = vec_add(screen_center, new_vector(-1, 1, 0)); //p0
	cam_right_top = vec_add(screen_center, new_vector(1, 1, 0)); //p1
 	cam_bottom_left = vec_add(screen_center, new_vector(-1, -1, 0)); //p2

	point_on_screen = add_3_vec(cam_left_top, 
					vec_multiply(vec_sub(cam_right_top, cam_left_top), u), 
					vec_multiply(vec_sub(cam_bottom_left, cam_left_top), v));

t_vec3 ray_dir = vec_sub(point_on_screen, scene->cam->origin);
 	return (vec_normalize(ray_dir));

//--------------------------------------------------------------------	 
	// t_ray	ray;
	// double	vp_height;
	// double	vp_width;
	// t_vec3	cam_horizon;
	// t_vec3	cam_verti;

	// ray.origin = scene->cam->origin;
	// vp_height = 2.0;
	// vp_width = 2.0;

	// cam_horizon = new_vector(vp_width, 0, 0);
	// cam_verti = new_vector(0, vp_height, 0);
	// // left_bottom + u * horizontal + v * vertical - origin 
	// ray.direction = vec_normalize(vec_sub(vec_add(vec_add(cam_bottom_left, vec_multiply(cam_horizon, u)), vec_multiply(cam_verti, v)),
    //                             scene->cam->origin));
	// return(ray.direction);

 }

void	ray_tracing(t_scene *scene)
{
	int	x;
	int	y;
	int	color;
	t_mlx	*mlx;
	t_vec3	dir;
	
	y = 0;
	mlx = get_mlx();
	while(y < mlx->height)
	{
		x = 0;
		while (x < mlx->width)
		{
			double u = (double)x / (mlx->width - 1);
			double v = (double)y / (mlx->height - 1);
			dir = get_ray_dir(scene, mlx, u, v);
		//	dir = rotate_dir(dir, scene);
			color = intersection(scene, dir); //faire une struct obj ou ou tab döbj
			my_mlx_pixel_put(mlx, x, y, color);
			x++;
		}
		y++;
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
	scene = ft_calloc(1, sizeof(t_scene));
	init_scene(scene);
	parse_machine(scene, argv[1]);
	make_scene(scene);
    return (0);
}