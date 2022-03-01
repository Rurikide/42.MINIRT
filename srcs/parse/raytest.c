#include "../../incls/mini_rt.h"

// CE NEST PAS NOTRE CODE !!! SOURCE ASHIAE GITHUB

t_vec3		multiply_by_matrix(t_vec3 p, t_matrix m)
{
	t_vec3 res;
	//	p = position d'origine actuelle de la camera. m = matrice [0]Right [1]Up [2]CamDir [3]CamOrigin
	res.x = p.x * m.d[0][0] + p.y * m.d[1][0] + p.z * m.d[2][0] + m.d[3][0];
	res.y = p.x * m.d[0][1] + p.y * m.d[1][1] + p.z * m.d[2][1] + m.d[3][1];
	res.z = p.x * m.d[0][2] + p.y * m.d[1][2] + p.z * m.d[2][2] + m.d[3][2];
	return (res);
}


// CETTE fonction setup le UP et RIGHT vector normalisé. plus contient cam unit dir, cam origin
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


t_ray		create_ray(t_vec3 origin, t_vec3 direction)
{
	t_ray result;

	result.origin = origin;
	result.direction = direction;
	return (result);
}

t_vec3		get_direction(int x, int y, t_scene *scene)
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

t_ray		ray_to_pixel(int x, int y, t_scene *scene)
{
	t_vec3		origin;
	t_vec3		direction;
	t_matrix	c2w;

	// matrice ayant le UP et RIGHT vector, les unit cam dir, cam origin
	c2w = look_at(scene->cam->origin, scene->cam->dir);

	// MULTIPLY BY MATRIX RETOUNRE UN VEC3, et non une matrice. 
	// obtient le nouvel origine de la camera qui était au départ est à 0,0,0. 
	origin = multiply_by_matrix(new_vector(0, 0, 0), c2w);

	direction = get_direction(x, y, scene);
	direction = multiply_by_matrix(direction, c2w);
	direction = vec_sub(direction, origin);
	direction = vec_normalize(direction);
	return (create_ray(origin, direction));
}

void	send_rays(t_scene *scene)
{
	int		x;
	int		y;
	int		color;


	x = 0;
	y = 0;
	while (y < get_mlx()->height)
	{
		x = 0;
		while (x < get_mlx()->width)
		{
			color = get_color(scene, ray_to_pixel(x, y, scene));
			info->image.addr[y * info->scene->width + x] = color;
			x++;
		}
		y++;
	}
}




// CAMERA


void	test_camera(t_scene *scene)
{
	t_mlx *mlx = get_mlx();
	double aspect_ratio = mlx->width / mlx->height;
	double	view_height = 2.0;
	double view_width = aspect_ratio * view_height;
	double focal_length = 1.0;

	t_ray ray;

	t_vec3 origin = scene->cam->origin;
	t_vec3 horizontal = new_vector(view_width, 0, 0);
	t_vec3 vertical = new_vector(0, view_height, 0);

	t_vec3  ll_corner = vec_sub(origin, vec_multiply(horizontal, 0.5));
	ll_corner = vec_sub(origin, vec_multiply(vertical, 0.5));
	ll_corner = vec_sub(origin, new_vector(0, 0, focal_length));


	for (int j = mlx->height - 1; j >= 0; --j)
	{
		for (int i = 0; i <= mlx->width; i++);
		{
			double u = (double)i / (mlx->width - 1);
			double v = (double)j / (mlx->height - 1);
			ray = create_ray(scene->cam->origin, vec_add(ll_corner, vec_sub(vec_add(vec_multiply(horizontal, u), vec_multiply(vertical, v)),origin)));
			t_rgb color = new_color(100,10, 20);
		}
	}

}

//   ray(const point3& origin, const vec3& direction)  : orig(origin), dir(direction)