#include "../cub3d.h"

static int	is_wall(t_scene *scene, int x, int y)
{
	int	cell_width;
	int	cell_height;

	cell_width = WIDTH / MAP_WIDTH;
	cell_height = HEIGHT / MAP_HEIGHT;
	if (scene->map[y / cell_height][x / cell_width] == 1)
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
}
