#include "../../cub3d.h"

int	check_extension(char *str)
{
	int		ext;

	ext = ft_strlen(str);
	if (ext <= 4)
	{
		ft_fprintf(2, "Error: Invalid name map\n");
		return (1);
	}
	if (ft_strncmp(&str[ext - 4], ".cub", 4) != 0)
	{
		ft_fprintf(2, "Error: Invalid file extension. Have to be .cub\n");
		return (1);
	}
	return (0);
}

int	read_fd(char *file, t_scene *scene)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_fprintf(2, "Error: Open file\n");
		return (1);
	}
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] == '1' || line[0] == ' ')
		{
			if (check_info(scene) != 0)
			{
				ft_fprintf(2, "Error: Missing textures or colors before map\n");
				free(line);
				close(fd);
				return (1);
			}
			if (parse_map(scene, line, fd) == 1)
			{
				ft_fprintf(2, "Error allocated memory\n");
				close(fd);
				return (1);
			}
		}
		else if (line[0] != '\n')
			check_line_type(scene, line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}


int	check_info(t_scene *scene)
{
	if (!scene->texture.north || !scene->texture.east
		|| !scene->texture.south || !scene->texture.west)
		return (1);
	if (!scene->floor.f || !scene->ceiling.c)
		return (2);
	return (0);
}
