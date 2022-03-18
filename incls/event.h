#ifndef EVENT_H
# define EVENT_H

# include "vector_3d.h"
# include "scene.h"

t_ray		ray_settings(t_vec3 origin, t_vec3 direction);
t_vec3		ray_pixel_to_world(t_scene *scene, int x, int y);
t_ray		ray_generator(t_scene *scene, int x, int y);
void		translation_signal_handler(int keycode, t_scene *scene);
void		translation_signal_ad(int keycode, t_scene *scene);
void		translation_signal_ws(int keycode, t_scene *scene);
void		translation_signal_rt(int keycode, t_scene *scene);
void		pitch_cam(int keycode, t_scene *s);
void		yaw_cam(int keycode, t_scene *s);
int		click_event(int	button, int x, int y, t_scene *scene);
void		matrix_look_at(t_scene *s);
t_matrix	matrix_identity(void);
t_matrix	matrix_product(t_matrix src, t_matrix mult);
t_matrix	matrix_rot_x(double degrees);
t_matrix	matrix_rot_y(double degrees);
t_matrix	new_matrix(t_vec3 origin, t_vec3 forward, t_vec3 right, t_vec3 up);
t_vec3		multiply_by_matrix(t_vec3 p, t_matrix m);
int			get_hit_color(t_scene *scene, t_ray ray);
void		sphere_resize(int button, t_scene *scene, t_shape *clic);
void        plane_event(int button, t_scene *scene, t_shape *clic);
void		plane_rotation(int keycode, t_scene *scene);
void		cylinder_event(int button, t_scene *scene, t_shape *clic);
void		cylinder_rotation(int keycode, t_scene *scene);
int		screen_mode(int keycode, t_scene *scene);
void		cylinder_height(int keycode, t_scene *scene);
void		free_shape(void * object);
void	close_minirt(void);
void	key_translation_ad(int keycode, t_scene *scene, t_vec3 *origin);
void	key_translation_ws(int keycode, t_scene *scene, t_vec3 *origin);
void	key_translation_rt(int keycode, t_scene *scene, t_vec3 *origin);

#endif
