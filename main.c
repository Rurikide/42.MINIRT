
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

	t_vec3 point_on_screen;
	t_ray	ray;
	t_vec3	cam_horizon;
	t_vec3	cam_verti;

	ray.origin = scene->cam->origin;
	cam_horizon = new_vector(scene->cam->view_p_w, 0, 0);
	cam_verti = new_vector(0, scene->cam->view_p_h, 0);
	/* Pour avoir le point sur l'écran on ajoute le vecteur left_bottom au vecteur qui goes along the screen width
	et on le multiplie par la position du pixel sur la width; Puis on ajoute le vecteur qui goes along the height 
	of the screen and multiply it by how far the pixel is on the height oh the screen*/
	point_on_screen = add_3_vec(scene->cam->bott_left, vec_multiply(cam_horizon, u), vec_multiply(cam_verti, v));
	ray.direction = vec_normalize(vec_sub(point_on_screen, ray.origin));
	return(ray.direction);

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
			double u = (double)x / (WIDTH);
			double v = (double)y / (HEIGHT);
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