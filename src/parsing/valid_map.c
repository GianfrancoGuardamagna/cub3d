#include "../../cub3d.h"

int	get_grid_rows(char **grid)
{
	int	i;

	i = 0;
	if (!grid)
		return (0);
	while (grid[i])
		i++;
	return (i);
}

char	**expand_grid(char **old_grid, char *new_line)
{
	char	**new_grid;
	int		rows;
	int		i;

	rows = get_grid_rows(old_grid);
	new_grid = malloc(sizeof(char *) * (rows + 2));
	if (!new_grid)
		return (NULL);
	i = 0;
	while (i < rows)
	{
		new_grid[i] = old_grid[i];
		i++;
	}
	new_grid[i] = new_line;
	new_grid[i + 1] = NULL;
	free(old_grid);
	return (new_grid);
}

int	parse_map(t_scene *scene, char *first_line, int fd)
{
	char	**tmp_grid;
	char	*line;

	scene->map.grid = malloc(sizeof(char *) * 2);
	if (!scene->map.grid)
	{
		ft_fprintf(2, "Error allocated memory\n");
		return (1);
	}
	scene->map.grid[0] = first_line;
	scene->map.grid[1] = NULL;
	line = get_next_line(fd);
	while (line)
	{
		tmp_grid = expand_grid(scene->map.grid, line);
		if (!tmp_grid)
			
	}
	return (0);
}
