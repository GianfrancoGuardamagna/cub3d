#include "../../cub3d.h"

int	is_open(t_scene *scene, int y, int x)
{
	if (y < 0 || y >= scene->map.rows || x < 0)
		return (1);
	if (x >= (int)ft_strlen(scene->map.grid[y]))
		return (1);
	if (scene->map.grid[y][x] == ' ' || scene->map.grid[y][x] == '\n')
		return (1);
	return (0);
}

int	touches_void(t_scene *scene, int y, int x)
{
	return (is_open(scene, y - 1, x) || is_open(scene, y + 1, x)
		|| is_open(scene, y, x - 1) || is_open(scene, y, x + 1));
}

int	check_close_map(t_scene *scene)
{
	int	y;
	int	x;

	y = 0;
	while (scene->map.grid[y])
	{
		x = 0;
		while (scene->map.grid[y][x])
		{
			if (ft_strchr("0NSEW", scene->map.grid[y][x])
				&& touches_void(scene, y, x))
			{
				ft_fprintf(2, "Error\nMap is not closed by walls\n");
				return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

