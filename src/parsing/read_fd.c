#include "../../cub3d.h"

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
			if (status != 0)
				drain_gnl(fd);
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
