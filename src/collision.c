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
