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
//! PUEDO QUITAR DE LOS PARAMETROS T_SCENE PORQUE NO LO USO
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

int	valid_rgb_format(char *line)
{
	int	i;

	if (count_commas(line) != 2)
	{
		ft_fprintf(2, "Error: No valid data ceiling or floor\n");
		return (1);
	}
	i = 0;
	while (line[i])
	{
		if (!ft_isdigit(line[i]) && line[i] != ',' && !ft_isspace(line[i]))
			return (1);
		else
			i++;
	}
	return (0);
}

//! QUITAR EL EXIT Y LLAMAR A CLEAN_EXIT
uint32_t	extract_color_numbers(char *line)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;

	if (valid_rgb_format(line) == 1)
		return (1);
	rgb = ft_split(line, ',');
	if (!rgb)
	{
		ft_fprintf(2, "Error allocated memory\n");
		return (1);
	}
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	ft_free_matrix(rgb);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		ft_fprintf(2, "Error: invalid color\n");
		return (1);
	}
	return ((r << 24) | (g << 16) | (b << 8) | 255);
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
