#include "../../cub3d.h"

int	check_row(char *row, int *players)
{
	int	x;

	x = 0;
	while (row[x] && row[x] != '\n')
	{
		if (!ft_strchr("01 NSEW", row[x]))
		{
			ft_fprintf(2, "Error\nInvalid character in map\n");
			return (1);
		}
		if (ft_strchr("NSEW", row[x]))
			(*players)++;
		x++;
	}
	return (0);
}

int	check_chars_and_player(t_scene *scene)
{
	int	y;
	int	players;

	y = 0;
	players = 0;
	while (scene->map.grid[y])
	{
		if (check_row(scene->map.grid[y], &players) == 1)
			return (1);
		y++;
	}
	if (players != 1)
	{
		ft_fprintf(2, "Error\nMap needs exactly one player\n");
		return (1);
	}
	return (0);
}

int	validate_map(t_scene *scene)
{
	if (check_chars_and_player(scene) == 1)
		return (1);
	if (check_close_map(scene) == 1)
		return (1);
	scene->map.cols = get_grid_cols(scene->map.grid);
	return (0);
}
