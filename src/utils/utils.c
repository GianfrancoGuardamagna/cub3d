#include "../../cub3d.h"

int	count_commas(char *line)
{
	int	i;
	int	commas;

	i = 0;
	commas = 0;
	while (line[i])
	{
		if (line[i] == ',')
			commas++;
		i++;
	}
	return (commas);
}

void	ft_free_matrix(char **array)
{
	int	i;

	if (!array)
		return ;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	clean_exit(t_scene *scene)
{
	if (!scene)
		return ;
	if (scene->texture.north)
		free(scene->texture.north);
	if (scene->texture.south)
		free(scene->texture.south);
	if (scene->texture.west)
		free(scene->texture.west);
	if (scene->texture.east)
		free(scene->texture.east);
	if (scene->floor.f)
		free(scene->floor.f);
	if (scene->ceiling.c)
		free(scene->ceiling.c);
	if (scene->map.grid)
		ft_free_matrix(scene->map.grid);
	free(scene);
}
