#ifndef MATRIX_H
# define MATRIX_H

# include "vector_3d.h"
# include "scene.h"


typedef enum e_getmat4elem
{
	m_origin,
	m_forward,
	m_backward,
	m_right,
	m_left,
	m_up,
	m_down
}	t_getmat4elem;

typedef struct s_mat4
{
	double			data[4][4];
}	t_mat4;

typedef double	t_real;
# define PI_2 6.28318531
# define M_EPSILON 1e-8
# define M_INFINITY 1.0e30f

# define ID_X 0
# define ID_Y 1
# define ID_Z 2

t_vec3		multiply_by_matrix(t_vec3 p, t_matrix m);
t_matrix	look_at(t_vec3 cam_ori, t_vec3 cam_dir);
t_ray		create_ray(t_vec3 origin, t_vec3 direction);
t_vec3		get_direction(t_scene *scene, int x, int y);
t_ray		ray_to_pixel(t_scene *scene, int x, int y);
int get_hit_color(t_scene *scene, t_ray ray);
t_vec3	rotate_dir(t_vec3 dir, t_scene *scene);
void	move_cam(int keycode, t_scene *scene);
t_vec3	tilt_cam(t_vec3 dir, double pan);
t_vec3	pan_cam(t_vec3 dir, double tilt);
#endif
