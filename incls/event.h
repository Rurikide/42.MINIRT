/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadia <jbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 13:24:16 by tshimoda          #+#    #+#             */
/*   Updated: 2022/03/24 15:55:06 by jbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENT_H
# define EVENT_H

# include "vector_3d.h"
# include "scene.h"

void		screen_mode(int keycode, t_scene *scene);
void		key_translation_ad(int keycode, t_scene *scene, t_vec3 *origin);
void		key_translation_ws(int keycode, t_scene *scene, t_vec3 *origin);
void		key_translation_rt(int keycode, t_scene *scene, t_vec3 *origin);
void		translation_signal_handler(int keycode, t_scene *scene);
void		translation_signal_ad(int keycode, t_scene *scene);
void		translation_signal_ws(int keycode, t_scene *scene);
void		translation_signal_rt(int keycode, t_scene *scene);
int			click_event(int button, int x, int y, t_scene *scene);
void		close_minirt(void);
void		*free_shape(void *object);
int			get_hit_color(t_scene *scene, t_ray ray);
void		sphere_resize(int button, t_scene *scene, t_shape *clic);
void		plane_event(t_scene *scene, t_shape *clic);
void		plane_rotation(int keycode, t_scene *scene);
void		cylinder_event(int button, t_scene *scene, t_shape *clic);
void		cylinder_rotation(int keycode, t_scene *scene);
void		cylinder_height(int keycode, t_scene *scene);
void		pitch_cam(int keycode, t_scene *s);
void		yaw_cam(int keycode, t_scene *s);

#endif
