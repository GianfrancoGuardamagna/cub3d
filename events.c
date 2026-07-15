#include "cub3d.h"

//UTILIZAR PARA GENERALIZAR LA SALIDA DE ERRORES
//void	throw_error(t_game *game, char *err_msg)
//{
//	ft_putendl_fd("Error", 2);
//	ft_putendl_fd(err_msg, 2);
//	cleanup(game);
//	exit(EXIT_FAILURE);
//}

//Hay que revisar las colisiones que andan mezzo mezzo
void	handle_move(t_scene *scene)
{
	double	move_x;
	double	move_y;
	double	right_x;
	double	right_y;
	double	old_dir_x;

	move_x = scene->player.dir_x * scene->player.speed;
	move_y = scene->player.dir_y * scene->player.speed;

	right_x = -scene->player.dir_y * scene->player.speed;
	right_y = scene->player.dir_x * scene->player.speed;

	if (mlx_is_key_down(scene->mlx_connection, MLX_KEY_W))
	{
		if(check_walls_around(scene, scene->player.pos_x + move_x, scene->player.pos_y + move_y))
			return ;
		scene->player.pos_x += move_x;
		scene->player.pos_y += move_y;
	}
	if (mlx_is_key_down(scene->mlx_connection, MLX_KEY_S))
	{
		if(check_walls_around(scene, scene->player.pos_x - move_x, scene->player.pos_y - move_y))
			return ;
		scene->player.pos_x -= move_x;
		scene->player.pos_y -= move_y;
	}
	if (mlx_is_key_down(scene->mlx_connection, MLX_KEY_D))
	{
		if(check_walls_around(scene, scene->player.pos_x + right_x, scene->player.pos_y + right_y))
			return ;
		scene->player.pos_x += right_x;
		scene->player.pos_y += right_y;
	}
	if (mlx_is_key_down(scene->mlx_connection, MLX_KEY_A))
	{
		if(check_walls_around(scene, scene->player.pos_x - right_x, scene->player.pos_y - right_y))
			return ;
		scene->player.pos_x -= right_x;
		scene->player.pos_y -= right_y;
	}
	if (mlx_is_key_down(scene->mlx_connection, MLX_KEY_LEFT))
	{
		old_dir_x = scene->player.dir_x;
		scene->player.dir_x = old_dir_x * cos(-3 * M_PI / 180) - scene->player.dir_y * sin(-3 * M_PI / 180);
		scene->player.dir_y = old_dir_x * sin(-3 * M_PI / 180) + scene->player.dir_y * cos(-3 * M_PI / 180);
	}
	if (mlx_is_key_down(scene->mlx_connection, MLX_KEY_RIGHT))
	{
		old_dir_x = scene->player.dir_x;
		scene->player.dir_x = old_dir_x * cos(3 * M_PI / 180) - scene->player.dir_y * sin(3 * M_PI / 180);
		scene->player.dir_y = old_dir_x * sin(3 * M_PI / 180) + scene->player.dir_y * cos(3 * M_PI / 180);
	}
	if (mlx_is_key_down(scene->mlx_connection, MLX_KEY_ESCAPE))
		close_handler(scene);
	
}

void	game_loop(void *param)
{
	t_scene	*scene;

	scene = param;
	handle_move(scene);
	analize_fov(scene);
	mlx_image_to_window(scene->mlx_connection, scene->img,
0, 0);
}

void	events_init(t_scene *scene)
{
//	mlx_key_hook(scene->mlx_connection, key_handler, scene);
	mlx_close_hook(scene->mlx_connection, &close_handler, scene);
	mlx_loop_hook(scene->mlx_connection, &game_loop, scene);
}

void	close_handler(void* param)
{
	t_scene *scene;
	int i;

	scene = param;
	if (scene->img)
		mlx_delete_image(scene->mlx_connection, scene->img);
	if(scene->texture.wall_E)
		mlx_delete_texture(scene->texture.wall_E);
	if(scene->texture.wall_W)
		mlx_delete_texture(scene->texture.wall_W);
	if(scene->texture.wall_S)
		mlx_delete_texture(scene->texture.wall_S);
	if(scene->texture.wall_N)
		mlx_delete_texture(scene->texture.wall_N);

	i = 0;
	while(i < MAP_HEIGHT)
	{
		free(scene->map[i]);
		i++;
	}
	free(scene->map);
	if (scene->mlx_connection)
		mlx_terminate(scene->mlx_connection);
	free(scene);
}

void	key_handler(mlx_key_data_t keydata, void* param)
{

	t_scene *scene;

	scene = param;

	if (keydata.action == MLX_PRESS && keydata.key == MLX_KEY_ESCAPE)
		close_handler(scene);
	//else if (keydata.action == MLX_PRESS && keydata.key == MLX_KEY_W)
	//{
	//	if(is_wall(scene, scene->player.pos_x + move_x, scene->player.pos_y + move_y))
	//		return ;
	//	scene->player.pos_x += move_x;
	//	scene->player.pos_y += move_y;
	//}
	//else if (mlx_is_key_down(scene->mlx_connection, MLX_KEY_S))
	//{
	//	if(is_wall(scene, scene->player.pos_x + right_x, scene->player.pos_y + right_y))
	//		return ;
	//	scene->player.pos_x -= move_x;
	//	scene->player.pos_y -= move_y;
	//}
	//else if (mlx_is_key_down(scene->mlx_connection, MLX_KEY_A))
	//{
	//	if(is_wall(scene, scene->player.pos_x - right_x, scene->player.pos_y - right_y))
	//		return ;
	//	scene->player.pos_x -= right_x;
	//	scene->player.pos_y -= right_y;
	//}
	//else if (mlx_is_key_down(scene->mlx_connection, MLX_KEY_D))
	//{
	//	if(is_wall(scene, scene->player.pos_x - move_x, scene->player.pos_y - move_y))
	//		return ;
	//	scene->player.pos_x += right_x;
	//	scene->player.pos_y += right_y;
	//}
	//else if (mlx_is_key_down(scene->mlx_connection, MLX_KEY_LEFT))
	//{
	//	//Its the transformation the vector (0, -1) into an angle (45°)
	//	old_dir_x = scene->player.dir_x;
	//	scene->player.dir_x = old_dir_x * cos(-3 * M_PI / 180) - scene->player.dir_y * sin(-3 * M_PI / 180);
	//	scene->player.dir_y = old_dir_x * sin(-3 * M_PI / 180) + scene->player.dir_y * cos(-3 * M_PI / 180);
	//}
	//else if (mlx_is_key_down(scene->mlx_connection, MLX_KEY_RIGHT))
	//{
	//	old_dir_x = scene->player.dir_x;
	//	scene->player.dir_x = old_dir_x * cos(3 * M_PI / 180) - scene->player.dir_y * sin(3 * M_PI / 180);
	//	scene->player.dir_y = old_dir_x * sin(3 * M_PI / 180) + scene->player.dir_y * cos(3 * M_PI / 180);
	//}

	analize_fov(scene);
	mlx_image_to_window(scene->mlx_connection, scene->img, 0, 0);
	return ;
}