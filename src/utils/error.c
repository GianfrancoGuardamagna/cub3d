#include "../../cub3d.h"

void	error_call(t_scene *scene, int status, char *msg)
{
	ft_fprintf(2, "Error\n%s\n", msg);
	clean_exit(scene);
	exit(status);
}

void	drain_gnl(int fd)
{
	char	*tmp;

	tmp = get_next_line(fd);
	while (tmp)
	{
		free(tmp);
		tmp = get_next_line(fd);
	}
}
