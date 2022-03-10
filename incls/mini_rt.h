#ifndef MINI_RT_H
# define MINI_RT_H

# include "color.h"
# include "matrix.h"
# include "parsing.h"
# include "vector_3d.h"
# include "scene.h"
# include "vector_array.h"

# include "../libft/libsrcs/libft.h"
# include "../libft/libsrcs/ft_printf.h"
# include "../libft/libsrcs/get_next_line.h"

# include "../libx/mlx.h"

#define INFINITY 1000
# define KEY_ESC 53 //ESCAPE
# define KEY_Q 12 // Q

# define KEY_A 0x00  //0
# define KEY_S 0x01  //1
# define KEY_D 0x02  //2
# define KEY_W 0x0D  //13

# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124

# define KEY_PLUS 24
# define KEY_MINUS 27

# define KEY_R 15
# define KEY_T 17

# define NUMPAD_2 84
# define NUMPAD_4 86
# define NUMPAD_6 88
# define NUMPAD_8 91

# define NUMPAD_5 87

# define NUMPAD_1 83
# define NUMPAD_3 85
# define NUMPAD_7 89
# define NUMPAD_9 92


# define WIDTH	1080
# define HEIGHT 720

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
int		key_event(int keycode, t_scene *scene);
int		click_close_window(void);
void	hook_collection(t_mlx *mlx, t_scene *scene);
void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);
t_mlx	*get_mlx(void);

/*MOVEMENTS
MOVE_CAM_C*/
void	move_cam(int keycode, t_scene *scene);
void	remake_scene(t_scene *scene, t_mlx *mlx);

/*SHAPES
SPHERE_C*/
t_vec3	get_norm_sphere(t_scene *scene, t_vec3	hit_p);
t_vec3	get_hit_point_sp(t_scene *scene, t_ray ray, double distance);
double	get_root(double disc, double b);
double	hit_sphere(void *sphere, t_vec3 cam, t_vec3 direction);
/*PLANE_C*/
double hit_plane(void *plan, t_vec3 ray_origin, t_vec3 ray_direction);


/*RAY_HIT
INTERSECTION_C*/
int		intersection(t_scene *scene, t_vec3 direction);
/*GET_COLOR_C*/
int	get_color(t_shape *obj, t_ray ray, t_scene *scene, double distance);
double	shadowing(t_vec3 hit_point, t_scene *scene, t_vec3 ray_dir);
double	spot_light(t_vec3 hit_point, t_scene *scene, t_vec3 norm);
double	spec_light(t_vec3 norm, t_vec3 dir, t_vec3 hit_point, t_scene *scene);


/*MAIN_C*/
void	ray_tracing(t_scene *scene);
t_vec3	get_ray_dir(t_scene *scene, t_mlx *mlx, double u, double v);
void	make_scene(t_scene *scene);

#endif