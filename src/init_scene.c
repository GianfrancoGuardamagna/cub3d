#include "../cub3d.h"

static unsigned long	createRGB(int r, int g, int b)
{
	return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

static void	loading_struct(t_scene *scene)
{
	scene->mlx_connection = mlx_init(WIDTH, HEIGHT, "cub3D", true);
	if (!scene->mlx_connection)
		error_call(scene, 2, "Failed to initialize graphic library");
	scene->img = mlx_new_image(scene->mlx_connection, WIDTH, HEIGHT);
	if (!scene->img)
		error_call(scene, 3, "Failed to initialize image");
	scene->texture.wall_N = mlx_load_png("./assets/wall_N.png");
	scene->texture.wall_S = mlx_load_png("./assets/wall_S.png");
	scene->texture.wall_E = mlx_load_png("./assets/wall_E.png");
	scene->texture.wall_W = mlx_load_png("./assets/wall_W.png");
	if (!scene->texture.wall_N || !scene->texture.wall_S || \
!scene->texture.wall_E || !scene->texture.wall_W)
		error_call(scene, 4, "Failed to initialize texture");
	scene->floor.color = createRGB(220, 110, 0);
	scene->ceiling.color = createRGB(225, 30, 0);
}

static void	populate_map(t_scene *scene, int map_width, \
int map_height, int map[][7])
{
	int	i;
	int	j;

	scene->map = malloc(sizeof(int *) * map_height);
	if (!scene->map)
		error_call(scene, 5, "Failed allocating memory");
	i = 0;
	while (i < map_height)
	{
		j = 0;
		scene->map[i] = malloc(sizeof(int) * map_width);
		if (!scene->map[i])
			error_call(scene, 5, "Failed allocating memory");
		while (j < map_width)
		{
			scene->map[i][j] = map[i][j];
			j++;
		}
		i++;
	}
}

void	init_scene(t_scene *scene)
{
	int	map[MAP_HEIGHT][MAP_WIDTH] = {
		{1, 1, 1, 1, 1, 1, 1}, 
		{1, 0, 0, 0, 0, 0, 1}, 
		{1, 0, 0, 1, 0, 0, 1}, 
		{1, 'N', 0, 0, 0, 0, 1}, 
		{1, 1, 1, 1, 1, 1, 1}};

	loading_struct(scene);
	populate_map(scene, MAP_WIDTH, MAP_HEIGHT, map);
}
