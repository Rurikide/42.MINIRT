#ifndef SCENE_H
# define SCENE_H

# include "vector_3d.h"
# include "vector_array.h"

typedef enum e_type
{
	SP = 1,
	CY = 2,
	PL = 3,
}	t_type;

typedef struct s_sp
{
	t_vec3	origin;
	double	rad;
	t_rgb	color;
}	t_sp;

typedef struct s_pl
{
	t_vec3	origin;
	t_vec3	dir;
	t_rgb	color;
}	t_pl;

typedef struct s_cy
{
	t_vec3	origin;
	t_vec3	dir;
	double	rad;
	double	height;
	t_rgb	color;
}	t_cy;

typedef struct s_shape
{
	void	*shape;
	double	(*hit_obj)(void *, t_vec3, t_vec3);
	int		type;
}	t_shape;

typedef struct s_amb
{
	double	ratio;
	t_rgb	color;
}	t_amb;

typedef struct s_cam
{
	t_vec3	origin;
	t_vec3	dir;
	int		fov;
}	t_cam;

typedef struct s_lit
{
	t_vec3	origin;
	double	ratio;
	t_rgb	color;
}	t_lit;

typedef struct s_scene
{
	t_amb		*amb;
	t_cam		*cam;
	t_lit		*lit;
	t_vector	*objs;
	int			init;
}	t_scene;

#endif