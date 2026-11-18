#include "cub3d.h"

static int	parse_scene(char *file, t_scene *scene)
{
	if (read_fd(file, scene) == 1)
		return (1);
	if (error_colors(scene) == 1)
		return (1);
	if (validate_map(scene) == 1)
		return (1);
	return (0);
}

static void	start_game(t_scene *scene)
{
	init_scene(scene);
	init_player(scene);
	init_events(scene);
	mlx_loop(scene->mlx_connection);
}

int	main(int ac, char **av)
{
	t_scene	*scene;

	if (ac != 2)
	{
		ft_fprintf(2, "Error\nUsage: ./cub3D map.cub\n");
		return (1);
	}
	if (check_extension(av[1]) != 0)
		return (1);
	scene = ft_calloc(1, sizeof(t_scene));
	if (!scene)
	{
		ft_fprintf(2, "Error\nMemory allocation failed\n");
		return (1);
	}
	if (parse_scene(av[1], scene) != 0)
	{
		clean_exit(scene);
		return (1);
	}
	start_game(scene);
	clean_exit(scene);
	return (0);
}
