#include "../../cub3d.h"

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

static void	free_graphics(t_scene *scene)
{
	if (scene->img && scene->mlx_connection)
		mlx_delete_image(scene->mlx_connection, scene->img);
	if (scene->texture.wall_e)
		mlx_delete_texture(scene->texture.wall_e);
	if (scene->texture.wall_w)
		mlx_delete_texture(scene->texture.wall_w);
	if (scene->texture.wall_s)
		mlx_delete_texture(scene->texture.wall_s);
	if (scene->texture.wall_n)
		mlx_delete_texture(scene->texture.wall_n);
	if (scene->mlx_connection)
		mlx_terminate(scene->mlx_connection);
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
	free_graphics(scene);
	free(scene);
}
