#ifndef MATRIX_H
# define MATRIX_H

# include "vector_3d.h"
# include "scene.h"

t_ray		ray_settings(t_vec3 origin, t_vec3 direction);
t_vec3		ray_pixel_to_world(t_scene *scene, int x, int y);
t_ray		ray_generator(t_scene *scene, int x, int y);
void		move_cam(int keycode, t_scene *scene);
int			mouse_event(int	button, int x, int y, t_scene *scene);
void		matrix_look_at(t_scene *s);
t_matrix	matrix_identity(void);
t_matrix	matrix_multi(t_matrix src, t_matrix mult);
t_matrix	matrix_rot_x(double degrees);
t_matrix	matrix_rot_y(double degrees);
t_matrix	new_matrix(t_vec3 origin, t_vec3 forward, t_vec3 right, t_vec3 up);
t_vec3		multiply_by_matrix(t_vec3 p, t_matrix m);
int			get_hit_color(t_scene *scene, t_ray ray);

#endif
