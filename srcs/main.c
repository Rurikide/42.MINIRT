#include "../incls/mini_rt.h"
#include "../libft/libsrcs/libft.h"
#include "../libft/libsrcs/ft_printf.h"
#include "../libft/libsrcs/get_next_line.h"
#include "../libx/mlx.h"

#include <stdio.h>

t_vec3		multiply_by_matrix(t_vec3 p, t_matrix m)
 {
 	t_vec3 res;
 	//	p = position d'origine actuelle de la camera. m = matrice [0]Right [1]Up [2]CamDir [3]CamOrigin
 	res.x = p.x * m.d[0][0] + p.y * m.d[1][0] + p.z * m.d[2][0] + m.d[3][0];
 	res.y = p.x * m.d[0][1] + p.y * m.d[1][1] + p.z * m.d[2][1] + m.d[3][1];
 	res.z = p.x * m.d[0][2] + p.y * m.d[1][2] + p.z * m.d[2][2] + m.d[3][2];
 	return (res);
}

t_matrix	look_at(t_vec3 cam_ori, t_vec3 cam_dir)
{
	t_matrix	m;
	t_vec3		random;
	t_vec3		right;
	t_vec3		up;

	random = new_vector(0, 1, 0);
	random = vec_normalize(random);
	right = vec_cross(random, cam_dir);
	right = vec_normalize(right);
	up = vec_cross(cam_dir, right);
	up = vec_normalize(up);
	m.d[0][0] = right.x;
	m.d[0][1] = right.y;
	m.d[0][2] = right.z;
	m.d[1][0] = up.x;
	m.d[1][1] = up.y;
	m.d[1][2] = up.z;
	m.d[2][0] = cam_dir.x;
	m.d[2][1] = cam_dir.y;
	m.d[2][2] = cam_dir.z;
	m.d[3][0] = cam_ori.x;
	m.d[3][1] = cam_ori.y;
	m.d[3][2] = cam_ori.z;
	return (m);
}

t_vec3	add_3_vec(t_vec3 u, t_vec3 v, t_vec3 w)
{
	t_vec3	resultante;

	resultante.x = u.x + v.x + w.x;
	resultante.y = u.y + v.y + w.y;
	resultante.z = u.z + v.z + w.z;
	return (resultante);
}

t_ray		create_ray(t_vec3 origin, t_vec3 direction)
{
	t_ray result;

	result.origin = origin;
	result.direction = direction;
	return (result);
}

t_vec3		get_direction(t_scene *scene, int x, int y)
{
	double fov_coeff;
	double aspect_ratio;
	double p_x;
	double p_y;

	fov_coeff = tan((double)scene->cam->fov / 2 * M_PI / 180);
	aspect_ratio = (double)get_mlx()->width / (double)get_mlx()->height;
	p_x = (2 * (x + 0.5) / (double)get_mlx()->width - 1) * aspect_ratio * fov_coeff;
	p_y = (1 - 2 * (y + 0.5) / (double)get_mlx()->height) * fov_coeff;
	return (new_vector(p_x, p_y, 1));
}


void	ray_tracing(t_scene *scene)
{
	t_mlx *mlx = get_mlx();
	int x = 0;
	int y = 0;
	int color = 0x123456;
	t_matrix world;
	t_ray ray;

	while (y < mlx->height)
	{
		x = 0;
		while (x < mlx->width)
		{
			world = look_at(scene->cam->origin, scene->cam->dir);
			t_vec3 dir = get_direction(scene, x, y);
			t_vec3 ori = multiply_by_matrix(new_vector(0, 0, 0), world);
			dir = vec_sub(dir, ori);
			dir = vec_normalize(dir);
			ray = create_ray(ori, dir);
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
 	{
 		printf("Error\n");
 		printf("Please select onr .rt file\n");
 		exit(EXIT_FAILURE);
 	}
 	scene = get_scene();
 	parse_machine(scene, argv[1]);
 	make_scene(scene);
     return (0);
 }