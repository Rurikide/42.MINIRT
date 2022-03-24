/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadia <jbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 15:33:58 by jbadia            #+#    #+#             */
/*   Updated: 2022/03/24 15:38:52 by jbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H

# include "color.h"
# include "event.h"
# include "matrix.h"
# include "parsing.h"
# include "scene.h"
# include "vector_3d.h"
# include "vector_3d2.h"
# include "vector_array.h"
# include "../libft/libsrcs/libft.h"
# include "../libft/libsrcs/get_next_line.h"
# include "../libx/mlx.h"

# define ANGLE 3.6
# define STEP 0.5
# define YES 1
# define NONE 0
# define MOUSE_LEFT 1
# define MOUSE_RIGHT 2
# define MOUSE_ROULETTE 3
# define ROULETTE_FORWARD 5
# define ROULETTE_BACKWARD 4
# define KEY_ESC 53
# define KEY_Q 12
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_W 13
# define KEY_R 15
# define KEY_T 17
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_PLUS 24
# define KEY_MINUS 27
# define KEY_PLUS_PETIT 43
# define KEY_PLUS_GRAND 47
# define KEY_L 37
# define X_AXIS 7
# define Y_AXIS 16
# define Z_AXIS 6
# define WIDTH	1080
# define HEIGHT 720
# define M_EPSILON 1e-8
# define M_INFINITY 1.0e30f

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

/*MLX_UTILS_C*/
int		key_event(int key, t_scene *scene);
int		click_close_window(void);
int		hook_collection(t_mlx *mlx, t_scene *scene);
void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);
t_mlx	*get_mlx(void);
void	make_scene(t_scene *scene);
void	remake_scene(t_scene *scene, t_mlx *mlx);

/*ROOTS_C*/
double	calc_root(double top_roco, double toprd, double h_2, double t);
double	get_root(double disc, double b);

static inline double	hit_sphere(void *sphere, t_vec3 ro, t_vec3 rd)
{
	double	b;
	double	c;
	double	disc;
	t_vec3	v;
	t_sp	*sp;

	sp = (t_sp *)sphere;
	v = vec_sub(ro, sp->origin);
	b = 2 * vec_dot(rd, v);
	c = vec_dot(v, v) - sp->rad * sp->rad;
	disc = b * b - 4 * c;
	if (disc >= 0)
		return (get_root(sqrtf(disc), b));
	else
		return (-1);
}

/*Si le discriminant est inférieur à 0, il n'y a pas 
d'intersection. Si p.t est supérieur à 0 mais 
inférieur à la H, le rayon touche le corps du cylindre
Sinon je vérifie si je suis dans les caps*/
static inline double	hit_cylinder(void *cylinder, t_vec3 r_o, t_vec3 rd)
{
	t_cy		*cyl;
	t_quadra	p;
	t_vec3		top;
	t_vec3		roco;
	double		h_2;

	cyl = (t_cy *)cylinder;
	top = vec_multiply(vec_normalize(vec_multiply(cyl->dir, cyl->height)),
			cyl->height);
	h_2 = vec_dot(top, top);
	roco = vec_sub(r_o, cyl->origin);
	p.a = h_2 - vec_dot(top, rd) * vec_dot(top, rd);
	p.b = h_2 * vec_dot(roco, rd) - vec_dot(top, roco) * vec_dot(top, rd);
	p.c = h_2 * vec_dot(roco, roco) - vec_dot(top, roco)
		* vec_dot(top, roco) - (cyl->rad) * (cyl->rad) * h_2;
	if ((p.b * p.b - p.a * p.c) < 0)
		return (-1);
	p.t1 = (-p.b - sqrtf((p.b * p.b - p.a * p.c))) / p.a;
	p.t = vec_dot(top, roco) + (p.t1) * vec_dot(top, rd);
	if (p.t > 0 && p.t < h_2)
		return (p.t1);
	p.t = calc_root(vec_dot(top, roco), vec_dot(top, rd), h_2, p.t);
	if (fabs(p.b + p.a * p.t) < sqrtf((p.b * p.b - p.a * p.c)))
		return (p.t);
	return (-1);
}

/*((origin_pl - origin_ray) ° norm_pl) / (ray_dir ° norm_pl)*/
static inline double	hit_plane(void *plan, t_vec3 r_o, t_vec3 rd)
{
	t_pl	*pl;
	double	a;
	double	b;
	double	t;

	pl = (t_pl *)plan;
	a = vec_dot(vec_sub(pl->origin, r_o), vec_normalize(pl->dir));
	b = vec_dot(rd, vec_normalize(pl->dir));
	t = a / b;
	return (t);
}

static inline t_vec3	get_cyl_norm(t_vec3 hit_p, t_cy *cyl)
{
	double	d;
	t_vec3	sum;
	t_vec3	norm;
	t_vec3	top;

	top = vec_add(cyl->origin, vec_multiply(vec_normalize(cyl->dir),
				cyl->height));
	if (vec_len(vec_sub(hit_p, cyl->origin)) < cyl->rad)
		norm = vec_multiply(cyl->dir, -1);
	else if (vec_len(vec_sub(hit_p, top)) < cyl->rad)
		norm = cyl->dir;
	else
	{
		d = vec_dot(vec_sub(hit_p, cyl->origin), vec_normalize(cyl->dir));
		sum = vec_add(cyl->origin, vec_multiply(cyl->dir, d));
		norm = vec_normalize(vec_sub(hit_p, sum));
	}
	return (norm);
}

/*RAY_HIT
GET_COLOR_C*/
int		get_color(t_shape *obj, t_ray ray, t_scene *scene, double distance);
double	shadow_ray(t_vec3 hit_point, t_scene *scene);
t_vec3	get_reflect(t_vec3 norm, t_vec3 ray_dir);
double	spot_light(t_vec3 hit_point, t_scene *scene, t_vec3 norm);
double	spec_light(t_vec3 norm, t_vec3 dir, t_vec3 hit_point, t_scene *scene);
/*LIGHT_C*/
t_rgb	get_diffuse_lit(t_rgb obj, t_scene *scene);
t_rgb	get_spec_lit(t_rgb obj,	double ks);
t_rgb	get_ambient_lit(t_scene *scene, t_rgb obj);

/*RAY.C */
int		get_hit_color(t_scene *scene, t_ray ray);
t_ray	ray_settings(t_vec3 origin, t_vec3 direction);
t_vec3	ray_pixel_to_world(t_scene *scene, int x, int y);
t_ray	ray_generator(t_scene *scene, int x, int y);
void	ray_tracing(t_scene *scene, int x, int y);

/*MAIN_C*/
void	remake_scene(t_scene *scene, t_mlx *mlx);
void	make_scene(t_scene *scene);

#endif