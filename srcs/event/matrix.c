#include "../incls/mini_rt.h"

t_matrix	new_matrix(t_vec3 origin, t_vec3 forward, t_vec3 right, t_vec3 up)
{
	t_matrix	new;

	new.d[0][0] = right.x;
	new.d[0][1] = right.y;
	new.d[0][2] = right.z;
	new.d[0][3] = 0;
	new.d[1][0] = up.x;
	new.d[1][1] = up.y;
	new.d[1][2] = up.z;
	new.d[1][3] = 0;
	new.d[2][0] = forward.x;
	new.d[2][1] = forward.y;
	new.d[2][2] = forward.z;
	new.d[2][3] = 0;
	new.d[3][0] = origin.x;
	new.d[3][1] = origin.y;
	new.d[3][2] = origin.z;
	new.d[3][3] = 1;
	return (new);
}

//An identity matrix is capable of multiplying any matrix with any order (dimensions) as long as it follows the next rules: 
t_matrix	matrix_identity(void)
{
	t_scene *scene;
	t_vec3	forward;
	t_vec3	up;
	t_vec3	right;
	t_vec3	origin;

	scene = get_scene();
	forward = scene->cam->dir;

	right = new_vector(0, 0, 1);
	up = new_vector(0, 1, 0);
	origin = new_vector(0, 0, 0);
	return (new_matrix(origin, forward, right, up));
}

t_matrix	matrix_rot_x(double degrees)
{
	t_matrix		rotate;
	double		radians;

	radians = degrees * M_PI / 180;
	rotate = matrix_identity();
	rotate.d[1][1] = cos(radians);
	rotate.d[1][2] = -sin(radians);
	rotate.d[2][1] = sin(radians);
	rotate.d[2][2] = cos(radians);
	return (rotate);
}

t_matrix	matrix_rot_y(double degrees)
{
	t_matrix		rotate;
	double		radians;

	radians = degrees * M_PI / 180;
	rotate = matrix_identity();
	rotate.d[0][0] = cos(radians);
	rotate.d[0][2] = sin(radians);
	rotate.d[2][0] = -sin(radians);
	rotate.d[2][2] = cos(radians);
	return (rotate);
}

t_matrix	matrix_multi(t_matrix src, t_matrix mult)
{
	static t_matrix		out;
	int			i;
	int			j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			out.d[i][j] = src.d[i][0] * mult.d[0][j] + src.d[i][1] * mult.d[1][j] + src.d[i][2] * mult.d[2][j] + src.d[i][3] * mult.d[3][j];
			j++;
		}
		i++;
	}
	return (out);
}

t_vec3		multiply_by_matrix(t_vec3 p, t_matrix m)
 {
 	t_vec3	res;

 	res.x = p.x * m.d[0][0] + p.y * m.d[1][0] + p.z * m.d[2][0] + m.d[3][0];
 	res.y = p.x * m.d[0][1] + p.y * m.d[1][1] + p.z * m.d[2][1] + m.d[3][1];
 	res.z = p.x * m.d[0][2] + p.y * m.d[1][2] + p.z * m.d[2][2] + m.d[3][2];
 	return (res);
}

void	matrix_look_at(t_scene *s)
{
	t_vec3		random;
	t_vec3		right;
	t_vec3		up;

	random = new_vector(0, 1, 0);
	right = vec_cross(random, s->cam->dir);
	right = vec_normalize(right);
	up = vec_cross(s->cam->dir, right);
	up = vec_normalize(up);
	s->cam->m.d[0][0] = right.x;
	s->cam->m.d[0][1] = right.y;
	s->cam->m.d[0][2] = right.z;
	s->cam->m.d[0][3] = 0;
	s->cam->m.d[1][0] = up.x;
	s->cam->m.d[1][1] = up.y;
	s->cam->m.d[1][2] = up.z;
	s->cam->m.d[1][3] = 0;
	s->cam->m.d[2][0] = s->cam->dir.x;
	s->cam->m.d[2][1] = s->cam->dir.y;
	s->cam->m.d[2][2] = s->cam->dir.z;
	s->cam->m.d[2][3] = 0;
	s->cam->m.d[3][0] = s->cam->origin.x;
	s->cam->m.d[3][1] = s->cam->origin.y;
	s->cam->m.d[3][2] = s->cam->origin.z;
	s->cam->m.d[3][3] = 1;
}