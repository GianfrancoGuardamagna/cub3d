#include "../cub3d.h"

int	is_wall_cell(t_scene *scene, int y, int x)
{
	if (is_open(scene, y, x))
		return (1);
	return (scene->map.grid[y][x] == '1');
}

static int	is_wall(t_scene *scene, int x, int y)
{
	if (x < 0 || y < 0)
		return (1);
	return (is_wall_cell(scene, y / CELL_SIZE, x / CELL_SIZE));
}

int	check_walls_around(t_scene *scene, int x, int y)
{
	if (is_wall(scene, x + PLAYER_RADIUS, y + PLAYER_RADIUS))
		return (1);
	if (is_wall(scene, x - PLAYER_RADIUS, y - PLAYER_RADIUS))
		return (1);
	if (is_wall(scene, x + PLAYER_RADIUS, y - PLAYER_RADIUS))
		return (1);
	if (is_wall(scene, x - PLAYER_RADIUS, y + PLAYER_RADIUS))
		return (1);
	return (0);
}



/* static int	is_wall(t_scene *scene, int x, int y)
{
	int	cell_width;
	int	cell_height;

	cell_width = WIDTH / MAP_WIDTH;
	cell_height = HEIGHT / MAP_HEIGHT;
	if (scene->map.grid[y / cell_height][x / cell_width] == '1')
		return (1);
	else
		return (0);
}

int	check_walls_around(t_scene *scene, int x, int y)
{
	if (is_wall(scene, x + PLAYER_RADIUS, y + PLAYER_RADIUS))
		return (1);
	if (is_wall(scene, x - PLAYER_RADIUS, y - PLAYER_RADIUS))
		return (1);
	if (is_wall(scene, x + PLAYER_RADIUS, y - PLAYER_RADIUS))
		return (1);
	if (is_wall(scene, x - PLAYER_RADIUS, y + PLAYER_RADIUS))
		return (1);
	return (0);
} */
