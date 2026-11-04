#include "../../cub3d.h"

int check_extension(char *str)
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
		check_line_type(scene, line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}

//! ME FALTA LA COMPROBACION DEL ELSE IF DEL SUELO Y DEL CIELO
/* int	check_line_type(t_scene *scene, char *line)
{
	if (!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2)
		|| !ft_strncmp(line, "WE", 2) || !ft_strncmp(line, "EA", 2))
		return (save_textures(scene, line));
	else if (line[0] != '\n')
		return (1);
	return (0);
} */

void	check_line_type(t_scene *scene, char *line)
{
	if (!ft_strncmp(line, "NO", 2) && !scene->texture.north)
		scene->texture.north = save_textures(line);
	else if (!ft_strncmp(line, "SO", 2) && !scene->texture.south)
		scene->texture.south = save_textures(line);
	else if (!ft_strncmp(line, "WE", 2) && !scene->texture.west)
		scene->texture.west = save_textures(line);
	else if (!ft_strncmp(line, "EA", 2) && !scene->texture.east)
		scene->texture.east = save_textures(line);
}
//! PUEDO QUITAR DE LOS PARAMETROS T_SCENE PORQUE NO LO USO
char	*save_textures(char *line)
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

int	check_info(t_scene *scene)
{
	if (!scene->texture.north || !scene->texture.east
		|| !scene->texture.south || !scene->texture.west)
		return (1);
	if (!scene->floor.f || !scene->ceiling.c)
		return (2);
	return (0);
}
