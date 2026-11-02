#include "../cub3d.h"

void	error_call(t_scene *scene, int status, char *msg)
{
	if (scene && msg && (status < 2147483647 && status > -2147483648))
	{
		printf("Error: %d, %s\n", status, msg);
		close_handler(scene);
		exit(status);
	}
	printf("Scene failed\n");
	close_handler(scene);
	exit(1);
}
