#include "../../cub3d.h"

void	check_line_type(t_scene *scene, char *line)
{
	if (!ft_strncmp(line, "NO", 2) && !scene->texture.north)
		scene->texture.north = extract_data(line);
	else if (!ft_strncmp(line, "SO", 2) && !scene->texture.south)
		scene->texture.south = extract_data(line);
	else if (!ft_strncmp(line, "WE", 2) && !scene->texture.west)
		scene->texture.west = extract_data(line);
	else if (!ft_strncmp(line, "EA", 2) && !scene->texture.east)
		scene->texture.east = extract_data(line);
	else if (!ft_strncmp(line, "F ", 2) && !scene->floor.f)
		scene->floor.f = extract_data(line);
	else if (!ft_strncmp(line, "C ", 2) && !scene->ceiling.c)
		scene->ceiling.c = extract_data(line);
}

char	*extract_data(char *line)
{
	int		i;
	char	*clean_path;

	i = 2;
	while (ft_isspace(line[i]))
		i++;
	clean_path = ft_strtrim(line + i, " \t\n");
	if (!clean_path)
		return (NULL);
	return (clean_path);
}
