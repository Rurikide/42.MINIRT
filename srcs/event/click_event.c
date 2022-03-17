#include "../incls/mini_rt.h"

t_shape	*get_hit_shape(t_scene *scene, t_ray ray)
{
	size_t	i;
	double	distance;
	double	closer;
	t_shape	*shape;
	t_shape	*obj;

	closer = INFINITY;
	shape = NULL;
	i = 0;
	while (i < scene->objs->total)
	{
		obj = (t_shape *)scene->objs->elements[i];
		distance = obj->hit_obj(obj->shape, ray.origin, ray.direction);
		if (distance > M_EPSILON && distance < closer)
		{
			closer = distance;
			shape = obj;
		}
		i++;
	}
	if (shape == NULL)
		return (NULL);
	return (shape);
}

int	mouse_event(int button, int x, int y, t_scene *scene)
{
	t_shape	*clic;
	t_ray	ray;

	ray = ray_generator(scene, x, y);
	clic = get_hit_shape(scene, ray);
	if (clic == NULL)
	{
		scene->screen.is_selected = 0;
		scene->select = NULL;
		printf("the ray didn't hit any object\n");
		return (0);
	}
	else if (button == MOUSE_RIGHT)
	{
		scene->screen.is_selected = NO;
		printf("selection cleared\n");
		return (0);
	}
	if (clic->type == SP)
        sphere_resize(button, scene, clic);
	if (clic->type == PL)
	{
		printf("PLANE SELECTED\n");
		plane_event(button, scene, clic);
	}
	return (0);
}
