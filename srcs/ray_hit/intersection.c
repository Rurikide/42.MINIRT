#include "../../incls/mini_rt.h"

/*fonction qui renvoi la couleur frappée par le rayon
on ne garde que la couleur de l'objet le plus proche de la cam*/
int	intersection(t_scene *scene, t_vec3 direction)
{
	int	i;
	double distance;
	double closer;
	int		color;	
	t_shape *obj;

	closer = 10000;
	color = 0x000000;
	i = 0;
	while (i < scene->objs->total)
	{
		obj = (t_shape *)scene->objs->elements[i];
		distance = obj->hit_obj(obj->shape, scene->cam->origin, direction);
		if (distance > 0 && distance < closer)
		{
			closer = distance;
			color = get_color(obj, direction, scene, distance);
		}
		i++;
	}
	return (color);
}


