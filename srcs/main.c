#include "../incls/mini_rt.h"
#include "../libft/libsrcs/libft.h"
#include "../libft/libsrcs/ft_printf.h"
#include "../libft/libsrcs/get_next_line.h"
#include "../libx/mlx.h"

#include <stdio.h>


//fonction pour gérer les ombres
double	shadow_ray(t_vec3 hit_point, t_scene *scene)
{
	size_t i;
	t_vec3 dir_lit;
	double distance;
	t_shape *obj;

	dir_lit = vec_normalize(vec_sub(scene->lit->origin, hit_point)); //vecteur qui part de la source de lumiere au hit_point
	i = 0;
	while (i < scene->objs->total)
	{
		obj = (t_shape *)scene->objs->elements[i];
		distance = obj->hit_obj(obj->shape, hit_point, dir_lit);
		/*si la distance est > 0 c'est que ca hit devant la cam
		mais si elle est inférieure à la len du vecteur, c'est qu'on intercepte un autre
		objet en chemin donc il va y avoir une ombre sur l'objet*/
		if (distance > 0 && distance < vec_len(vec_sub(scene->lit->origin, hit_point))
			&& scene->objs->elements[i - 1] != i) 
			return (-1); // je suis dans le spot_light
		i++;
	}
	return (0);
}

double	spec_light(t_vec3 norm, t_vec3 dir, t_vec3 hit_point, t_scene *scene)
{
	t_vec3 reflet;
	t_vec3 spot;

	spot = vec_normalize(vec_sub(scene->lit->origin, hit_point));
	reflet = vec_normalize(vec_sub(dir, vec_multiply(norm, 2 * vec_dot(norm, dir))));
	return (pow(fmax(vec_dot(reflet, spot), 0), 32) * scene->lit->ratio);
}

/*Calcul l'angle formé par le vecteur du spot_light et le vecteur du hit_point
Spot_light se situe entre -1 et 1, sachant que 0 est l'angle qui donne la lumière
la plus intense car directement face au point d'intersection*/
double	spot_light(t_vec3 hit_point, t_scene *scene, t_vec3 norm)
{
	t_vec3	spot;
	double	spot_light;

	spot = vec_normalize(vec_sub(scene->lit->origin, hit_point));
	spot_light = vec_dot(norm, spot) * scene->lit->ratio; 
	return (spot_light);
}

int	get_color(t_shape *obj, t_vec3 direction, t_scene *scene, double distance)
{
	t_vec3	hit_point;
	t_vec3 norm;
	int	color;
	int	i;
	double shadow;
	double	test;

	i = 0;
	hit_point = get_hit_point_sp(scene, direction, distance);
	if (obj->type == 1)
		norm = vec_normalize(vec_sub(hit_point, ((t_sp *)obj->shape)->origin));
	shadow = shadow_ray(hit_point, scene); 
	if (shadow == 0) //il n'y a rien qui interfère entremon objet et la lumière, donc je dois afficher la couleu de l'objet en tenant compte des lumières
		color = add_3_colors(multiply_color(rgb_to_int((((t_sp *)obj->shape)->color)), scene->amb->ratio), 
		multiply_color(rgb_to_int((((t_sp *)obj->shape)->color)), spot_light(hit_point, scene, norm)), 
		multiply_color(rgb_to_int((((t_sp *)obj->shape)->color)), spec_light(norm, direction, hit_point, scene))); 
	else //il y a un objet entre ma lumière et mon objet, je dois afficher de l'ombre sur ledit objet
	{
		color = add_color(
			add_3_colors((multiply_color(rgb_to_int((((t_sp *)obj->shape)->color)), scene->amb->ratio)), 
			multiply_color(rgb_to_int((((t_sp *)obj->shape)->color)), spot_light(hit_point, scene, norm)), 0)
			,-30);
	}
	return (color);
}


t_vec3	get_hit_point_sp(t_scene *scene, t_vec3 direction, double distance)
{
	t_vec3	hit_p;

	hit_p = vec_add(vec_multiply(direction, distance), scene->cam->origin);
	return (hit_p);
}

double	get_root(double disc, double b)
{
  double	t1;
  double	t2;
  double	t;
  double	min;
  double	max;
	

	t1 = -b + sqrt(disc)/2;
	t2 = -b - sqrt(disc)/2;
	min = fmin(t1, t2);
	max = fmax(t1, t2);
	if (min >= 0)
		t = min;
	else
		t = max;
	return (t);
}

double hit_sphere(void *sphere, t_vec3 cam, t_vec3 direction)
{
	double	b;
	double	c;
	double	disc;
	t_vec3	v;
	t_sp *sp;

	sp = (t_sp *)sphere;
	v = vec_sub(cam, sp->origin);
	b = 2 * vec_dot(direction, v);
	c = vec_dot(v, v) - sp->rad * sp->rad;
	disc = b * b - 4*c;
	if (disc >= 0)
		return (get_root(disc, b));
	else
		return (0);
}
	

int get_hit_color(t_scene *scene, t_ray ray)
{
	// aka intersection
	int	i;
	double distance;
	double closer;
	int		color;	
	t_shape *obj;

	closer = INFINITY;
	color = 0x000000;
	i = 0;
	while (i < scene->objs->total)
	{
		obj = (t_shape *)scene->objs->elements[i];
		distance = obj->hit_obj(obj->shape, ray.origin, ray.direction);
		if (distance > 0 && distance < closer)
		{
			closer = distance;
			color = get_color(obj, ray.direction, scene, distance);
		}
		i++;
	}
	return (color);
}

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

t_ray	ray_to_pixel(t_scene *scene, int x, int y)
{
	t_matrix world;
	t_ray ray;
		world = look_at(scene->cam->origin, scene->cam->dir);
		t_vec3 ori = multiply_by_matrix(new_vector(0, 0, 0), world);
		t_vec3 dir = get_direction(scene, x, y);
		dir = multiply_by_matrix(dir, world);
		dir = vec_sub(dir, ori);
		dir = vec_normalize(dir);
		ray = create_ray(ori, dir);
	return(ray);
}

void	ray_tracing(t_scene *scene)
{
	t_mlx *mlx = get_mlx();
	int x = 0;
	int y = 0;
	int color = 0x123456;
	t_ray ray;
	while (y < mlx->height)
	{
		x = 0;
		while (x < mlx->width)
		{
			ray = ray_to_pixel(scene, x, y);
			color = get_hit_color(scene, ray);
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