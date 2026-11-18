#include "cub3d.h"

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
	if (mlx_is_key_down(scene->mlx_connection, MLX_KEY_A))
		moving_west(scene, right_x, right_y);
	if (mlx_is_key_down(scene->mlx_connection, MLX_KEY_D))
		moving_east(scene, right_x, right_y);
	if (scene->camera == -1)
		handle_camera_keys(scene);
}

static void	game_loop(void *param)
{
	t_scene	*scene;

	scene = param;
	handle_move(scene);
	analize_fov(scene);
	paint_mapcell(scene);
}

void	init_events(t_scene *scene)
{
	mlx_loop_hook(scene->mlx_connection, &game_loop, scene);
	mlx_cursor_hook(scene->mlx_connection, &handle_camera_mouse, scene);
	mlx_key_hook(scene->mlx_connection, &handle_key_event, scene);
}
