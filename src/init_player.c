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


/* static void	dir_vector(t_scene *scene, int i, int j)
{
	if (scene->map[i][j] == 'N')
	{
		scene->player.dir_x = 0;
		scene->player.dir_y = -1;
	}
	else if (scene->map[i][j] == 'S')
	{
		scene->player.dir_x = 0;
		scene->player.dir_y = 1;
	}
	else if (scene->map[i][j] == 'E')
	{
		scene->player.dir_x = 1;
		scene->player.dir_y = 0;
	}
	else if (scene->map[i][j] == 'W')
	{
		scene->player.dir_x = -1;
		scene->player.dir_y = 0;
	}
}

void	init_player(t_scene *scene)
{
	int	cell_width;
	int	cell_height;
	int	i;
	int	j;

	cell_width = WIDTH / MAP_WIDTH;
	cell_height = HEIGHT / MAP_HEIGHT;
	i = 0;
	while (i < MAP_HEIGHT)
	{
		j = 0;
		while (j < MAP_WIDTH)
		{
			if (scene->map[i][j] == 'N' || \
scene->map[i][j] == 'S' || \
scene->map[i][j] == 'W' || \
scene->map[i][j] == 'E')
			{
				scene->player.pos_x = (cell_width * (j + 1)) - (cell_width / 2);
				scene->player.pos_y = (cell_height * (i + 1)) \
- (cell_height / 2);
				dir_vector(scene, i, j);
				scene->player.speed = 10;
				return ;
			}
			j++;
		}
		i++;
	}
} */
