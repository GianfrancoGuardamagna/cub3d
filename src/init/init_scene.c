#include "../cub3d.h"

static void	load_texture(t_scene *scene, mlx_texture_t **dst, char *path)
{
	*dst = mlx_load_png(path);
	if (!*dst)
	{
		ft_fprintf(2, "Error\nCannot load texture: %s\n", path);
		clean_exit(scene);
		exit(1);
	}
}

void	init_scene(t_scene *scene)
{
	load_texture(scene, &scene->texture.wall_n, scene->texture.north);
	load_texture(scene, &scene->texture.wall_s, scene->texture.south);
	load_texture(scene, &scene->texture.wall_e, scene->texture.east);
	load_texture(scene, &scene->texture.wall_w, scene->texture.west);
	scene->mlx_connection = mlx_init(WIDTH, HEIGHT, "cub3D", true);
	if (!scene->mlx_connection)
		error_call(scene, 2, "Failed to initialize graphic library");
	scene->img = mlx_new_image(scene->mlx_connection, WIDTH, HEIGHT);
	if (!scene->img)
		error_call(scene, 3, "Failed to initialize image");
	if (mlx_image_to_window(scene->mlx_connection, scene->img, 0, 0) < 0)
		error_call(scene, 3, "Failed to display image");
	scene->camera = -1;
}
