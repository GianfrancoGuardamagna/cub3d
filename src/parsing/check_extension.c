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

int	check_info(t_scene *scene)
{
	if (!scene->texture.north || !scene->texture.east
		|| !scene->texture.south || !scene->texture.west)
	{
		ft_fprintf(2, "Error: Missing textures\n");
		return (1);
	}
	if (!scene->floor.f || !scene->ceiling.c)
	{
		ft_fprintf(2, "Error: Missing floor or ceiling color\n");
		return (1);
	}
	return (0);
}

static int	handle_map_start(t_scene *scene, char *line, int fd)
{
	if (check_info(scene) != 0)
	{
		free(line);
		return (1);
	}
	if (parse_map(scene, line, fd) == 1)
	{
		ft_fprintf(2, "Error allocated memory\n");
		return (1);
	}
	return (0);
}

static int	check_eof_errors(t_scene *scene)
{
	if (check_info(scene) != 0)
		return (1);
	ft_fprintf(2, "Error: No map found in file\n");
	return (1);
}

int	read_fd(char *file, t_scene *scene)
{
	int		fd;
	char	*line;
	int		status;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (ft_fprintf(2, "Error: Open file\n"), 1);
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] == '1' || line[0] == ' ')
		{
			status = handle_map_start(scene, line, fd);
			close(fd);
			return (status);
		}
		else if (line[0] != '\n')
			check_line_type(scene, line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (check_eof_errors(scene));
}
