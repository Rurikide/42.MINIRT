// // rotate_bonus.c

// t_bool	rotate(t_scene *scene, t_mat4 *mat)
// {
// 	const t_vec3	identity = (t_vec3){SHAPE_ROT, SHAPE_ROT, SHAPE_ROT};
// 	t_vec3			mult;

// 	mult = vec3_mult(identity, scene->selection_axis);
// 	*mat = mat4_mult(mat4_rotx(mult.x), *mat);
// 	*mat = mat4_mult(mat4_roty(mult.y), *mat);
// 	*mat = mat4_mult(mat4_rotz(mult.z), *mat);
// 	return (true);
// }


// // shape_axis_bonus.c

// t_bool	sh_set_axis_x(t_scene *scene)
// {
// 	if (scene->selection_mode == SELECTION_UNDEFINED)
// 		return (false);
// 	scene->selection_axis = vec3_id(ID_X);
// 	scene->do_update = false;
// 	console_put(SET_AXIS_X);
// 	return (true);
// }

// // transform_x_bonus.c
// t_bool	pitch_up(t_scene *scene)
// {
// 	scene->camera->world = mat4_mult(mat4_rotx(CAM_LOOK),
// 			scene->camera->world);
// 	return (true);
// }

// t_bool	pitch_down(t_scene *scene)
// {
// 	scene->camera->world = mat4_mult(mat4_rotx(-CAM_LOOK),
// 			scene->camera->world);
// 	return (true);
// }

// // mat4_mult.c
// t_mat4	mat4_mult(t_mat4 src, t_mat4 mult)
// {
// 	t_mat4		out;
// 	int			i;
// 	int			j;

// 	i = 0;
// 	while (i < 4)
// 	{
// 		j = 0;
// 		while (j < 4)
// 		{
// 			out.data[i][j] = src.data[i][0] * mult.data[0][j]
// 				+ src.data[i][1] * mult.data[1][j]
// 				+ src.data[i][2] * mult.data[2][j]
// 				+ src.data[i][3] * mult.data[3][j];
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (out);
// }


// // mat4_rotation.c

// t_mat4	mat4_rotz(t_real degrees)
// {
// 	t_mat4		rotate;
// 	t_real		radians;

// 	radians = degrees * M_PI / 180;
// 	rotate = mat4_identity();
// 	rotate.data[0][0] = cos(radians);
// 	rotate.data[0][1] = -sin(radians);
// 	rotate.data[1][0] = sin(radians);
// 	rotate.data[1][1] = cos(radians);
// 	return (rotate);
// }

// t_mat4	mat4_roty(t_real degrees)
// {
// 	t_mat4		rotate;
// 	t_real		radians;

// 	radians = degrees * M_PI / 180;
// 	rotate = mat4_identity();
// 	rotate.data[0][0] = cos(radians);
// 	rotate.data[0][2] = sin(radians);
// 	rotate.data[2][0] = -sin(radians);
// 	rotate.data[2][2] = cos(radians);
// 	return (rotate);
// }

// t_mat4	mat4_rotx(t_real degrees)
// {
// 	t_mat4		rotate;
// 	t_real		radians;

// 	radians = degrees * M_PI / 180;
// 	rotate = mat4_identity();
// 	rotate.data[1][1] = cos(radians);
// 	rotate.data[1][2] = -sin(radians);
// 	rotate.data[2][1] = sin(radians);
// 	rotate.data[2][2] = cos(radians);
// 	return (rotate);
// }

// t_mat4	mat4_rotate(const t_vec3 rotate)
// {
// 	return (mat4_mult(mat4_mult(
// 				mat4_rotz(rotate.z)
// 				, mat4_roty(rotate.y)), mat4_rotx(rotate.x)));
// }





/*
**	Retrieve vectors within matrix
**	mat4_get(matrix, type)
**	type specifiers:
**		m_right, m_up, m_forward, m_origin
*/

// t_vec3	mat4_get(t_mat4 m4, t_getmat4elem get)
// {
// 	if (get == m_right)
// 		return ((t_vec3){m4.data[0][0], m4.data[0][1], m4.data[0][2]});
// 	if (get == m_up)
// 		return ((t_vec3){m4.data[1][0], m4.data[1][1], m4.data[1][2]});
// 	if (get == m_forward)
// 		return ((t_vec3){m4.data[2][0], m4.data[2][1], m4.data[2][2]});
// 	if (get == m_origin)
// 		return ((t_vec3){m4.data[3][0], m4.data[3][1], m4.data[3][2]});
// 	return (vec3_zero());
// }


/*
**	Retrieve vectors within matrix
**	mat4_get(matrix, type)
**	type specifiers:
**		m_right, m_up, m_forward, m_origin
*/

// t_vec3	mat4_get(t_mat4 m4, t_getmat4elem get)
// {
// 	if (get == m_right)
// 		return ((t_vec3){m4.data[0][0], m4.data[0][1], m4.data[0][2]});
// 	if (get == m_up)
// 		return ((t_vec3){m4.data[1][0], m4.data[1][1], m4.data[1][2]});
// 	if (get == m_forward)
// 		return ((t_vec3){m4.data[2][0], m4.data[2][1], m4.data[2][2]});
// 	if (get == m_origin)
// 		return ((t_vec3){m4.data[3][0], m4.data[3][1], m4.data[3][2]});
// 	return (vec3_zero());
// }



// t_mat4	mat4_identity(void)
// {
// 	t_vec3	right;
// 	t_vec3	up;
// 	t_vec3	forward;
// 	t_vec3	zeroed;

// 	right = vec3_id(ID_X); // 1.0, 0.0, 0.0
// 	up = vec3_id(ID_Y); // 0.0, 1.0, 0.0
// 	forward = vec3_id(ID_Z); // 0.0, 0.0, 1.0
// 	zeroed = vec3_zero();
// 	return (mat4(zeroed, forward, right, up));
// }

// ID_X 0, ID_Y 1, ID_Z 2


// t_vec3	vec3_id(const int id)
// {
// 	const t_vec3	identity[3] = {
// 		(t_vec3){1.0, 0.0, 0.0},
// 		(t_vec3){0.0, 1.0, 0.0},
// 		(t_vec3){0.0, 0.0, 1.0}
// 	};

// 	return (identity[id]);
// }
