#include "../../cub3d.h"

int	check_extension(char *str)
{
	int		ext;

	ext = ft_strlen(str);
	if (ext <= 4)
	{
		ft_fprintf(2, "Error\nInvalid name map\n");
		return (1);
	}
	if (ft_strncmp(&str[ext - 4], ".cub", 4) != 0)
	{
		ft_fprintf(2, "Error\nInvalid file extension. Have to be .cub\n");
		return (1);
	}
	return (0);
}

int	check_info(t_scene *scene)
{
	if (!scene->texture.north || !scene->texture.east
		|| !scene->texture.south || !scene->texture.west)
	{
		ft_fprintf(2, "Error\nMissing textures\n");
		return (1);
	}
	if (!scene->floor.f || !scene->ceiling.c)
	{
		ft_fprintf(2, "Error\nMissing floor or ceiling color\n");
		return (1);
	}
	return (0);
}

int	handle_map_start(t_scene *scene, char *line, int fd)
{
	if (check_info(scene) != 0)
	{
		free(line);
		return (1);
	}
	if (parse_map(scene, line, fd) == 1)
	{
		ft_fprintf(2, "Error\n Memory allocation failed\n");
		return (1);
	}
	return (0);
}

int	check_eof_errors(t_scene *scene)
{
	if (check_info(scene) != 0)
		return (1);
	ft_fprintf(2, "Error\nNo map found in file\n");
	return (1);
}

