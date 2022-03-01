#ifndef MATRIX_H
# define MATRIX_H

# include "vector_3d.h"
# include "scene.h"

typedef struct	s_matrix
{
	double d[4][4];
}				t_matrix;

t_vec3		multiply_by_matrix(t_vec3 p, t_matrix m);
t_matrix	look_at(t_vec3 cam_ori, t_vec3 cam_dir);
t_ray		create_ray(t_vec3 origin, t_vec3 direction);
t_vec3		get_direction(int x, int y, t_scene *scene);
t_ray		ray_to_pixel(int x, int y, t_scene *scene);
#endif