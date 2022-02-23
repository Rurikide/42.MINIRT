

#ifndef MINI_RT_H
# define MINI_RT_H

# include "color.h"
# include "parsing.h"
# include "vector_3d.h"
# include "scene.h"
# include "vector_array.h"


# include "../libft/libsrcs/libft.h"
# include "../libft/libsrcs/ft_printf.h"
# include "../libft/libsrcs/get_next_line.h"

# include "../minilibx_opengl/mlx.h"

# define KEY_ESC 53 //ESCAPE
# define KEY_Q 12 // Q

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

typedef struct s_rt
{
	int	height;
	int	width;
	void	*img_ptr;
	t_scene	*scene;
	
}				t_rt;

t_mlx	*get_mlx(void);
void	init_rt(t_rt *rt);

int		key_event(int keycode, t_mlx *mlx);
int		click_close_window(void);
void	hook_collection(t_mlx *mlx);
void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);

t_sphere	*init_sphere();
t_cam	*init_cam();
t_scene *init_scene();
t_lit	*init_light();
t_vec3	get_norm_sphere(t_scene *scene, t_vec3	hit_p);
t_vec3	get_hit_point_sp(t_scene *scene, t_vec3 direction, double distance);
double	get_root(double disc, double b);
double hit_sphere(t_vec3 cam, t_vec3	direction, t_sphere *sphere);

double	find_dist(t_sphere *sphere, t_vec3 cam, t_vec3 direction);
int	intersection(t_scene *scene, t_vec3 direction);
int	get_color(t_sphere *sphere, t_vec3 direction, t_scene *scene, double distance);
double	shadowing(t_vec3 hit_point, t_scene *scene);




#endif