#include "cub3d.h"

static void	handle_camera(t_scene *scene)
{
	float	old_dir_x;

	if (mlx_is_key_down(scene->mlx_connection, MLX_KEY_LEFT))
	{
		old_dir_x = scene->player.dir_x;
		scene->player.dir_x = old_dir_x * cos(-3 * M_PI / 180) - \
scene->player.dir_y * sin(-3 * M_PI / 180);
		scene->player.dir_y = old_dir_x * sin(-3 * M_PI / 180) + \
scene->player.dir_y * cos(-3 * M_PI / 180);
	}
	if (mlx_is_key_down(scene->mlx_connection, MLX_KEY_RIGHT))
	{
		old_dir_x = scene->player.dir_x;
		scene->player.dir_x = old_dir_x * cos(3 * M_PI / 180) - \
scene->player.dir_y * sin(3 * M_PI / 180);
		scene->player.dir_y = old_dir_x * sin(3 * M_PI / 180) + \
scene->player.dir_y * cos(3 * M_PI / 180);
	}
}

static void	handle_move(t_scene *scene)
{
	float	move_x;
	float	move_y;
	float	right_x;
	float	right_y;

	move_x = scene->player.dir_x * scene->player.speed;
	move_y = scene->player.dir_y * scene->player.speed;
	right_x = -scene->player.dir_y * scene->player.speed;
	right_y = scene->player.dir_x * scene->player.speed;
	if (mlx_is_key_down(scene->mlx_connection, MLX_KEY_W))
		moving_north(scene, move_x, move_y);
	if (mlx_is_key_down(scene->mlx_connection, MLX_KEY_S))
		moving_south(scene, move_x, move_y);
	if (mlx_is_key_down(scene->mlx_connection, MLX_KEY_D))
		moving_west(scene, right_x, right_y);
	if (mlx_is_key_down(scene->mlx_connection, MLX_KEY_E))
		moving_east(scene, right_x, right_y);
	handle_camera(scene);
	if (mlx_is_key_down(scene->mlx_connection, MLX_KEY_ESCAPE))
		close_handler(scene);
}

static void	game_loop(void *param)
{
	t_scene	*scene;

	scene = param;
	handle_move(scene);
	analize_fov(scene);
	mlx_image_to_window(scene->mlx_connection, scene->img, 0, 0);
}

void	close_handler(void *param)
{
	t_scene	*scene;
	int		i;

	scene = param;
	if (scene->img)
		mlx_delete_image(scene->mlx_connection, scene->img);
	if (scene->texture.wall_E)
		mlx_delete_texture(scene->texture.wall_E);
	if (scene->texture.wall_W)
		mlx_delete_texture(scene->texture.wall_W);
	if (scene->texture.wall_S)
		mlx_delete_texture(scene->texture.wall_S);
	if (scene->texture.wall_N)
		mlx_delete_texture(scene->texture.wall_N);
	i = 0;
	while (i < MAP_HEIGHT)
	{
		free(scene->map[i]);
		i++;
	}
	free (scene->map);
	if (scene->mlx_connection)
		mlx_terminate(scene->mlx_connection);
	free (scene);
}

void	init_events(t_scene *scene)
{
	mlx_close_hook(scene->mlx_connection, &close_handler, scene);
	mlx_loop_hook(scene->mlx_connection, &game_loop, scene);
}
