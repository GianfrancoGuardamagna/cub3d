#include "../cub3d.h"

static void	dir_vector(t_scene *scene, char c)
{
	scene->player.dir_x = 0;
	scene->player.dir_y = 0;
	if (c == 'N')
		scene->player.dir_y = -1;
	else if (c == 'S')
		scene->player.dir_y = 1;
	else if (c == 'E')
		scene->player.dir_x = 1;
	else if (c == 'W')
		scene->player.dir_x = -1;
}

static int	is_spawn(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

void	init_player(t_scene *scene)
{
	int	i;
	int	j;

	i = 0;
	while (scene->map.grid[i])
	{
		j = 0;
		while (scene->map.grid[i][j])
		{
			if (is_spawn(scene->map.grid[i][j]))
			{
				scene->player.pos_x = j * CELL_SIZE + CELL_SIZE / 2;
				scene->player.pos_y = i * CELL_SIZE + CELL_SIZE / 2;
				dir_vector(scene, scene->map.grid[i][j]);
				scene->player.speed = 10;
				return ;
			}
			j++;
		}
		i++;
	}
}
