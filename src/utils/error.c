#include "../../cub3d.h"

int	error_colors(t_scene *scene)
{
	if (extract_color_numbers(scene->floor.f, &scene->floor.color) == 1
		|| extract_color_numbers(scene->ceiling.c, &scene->ceiling.color) == 1)
	{
		clean_exit(scene);
		return (1);
	}
	return (0);
}
