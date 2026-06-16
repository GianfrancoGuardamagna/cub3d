#include "cub3d.h"

void	scene_cleanup(t_scene *scene)
{
	if (scene->img.img_ptr)
		mlx_destroy_image(scene->mlx_connection, scene->img.img_ptr);
	if (scene->mlx_window)
		mlx_destroy_window(scene->mlx_connection, scene->mlx_window);
	if (scene->mlx_connection)
	{
		mlx_destroy_display(scene->mlx_connection);
		free(scene->mlx_connection);
	}
	exit(1);
}

void	events_init(t_scene *scene)
{
	mlx_hook(scene->mlx_window, KeyPress, KeyPressMask, key_handler, scene);
	mlx_hook(scene->mlx_window, DestroyNotify, StructureNotifyMask, close_handler, scene);
}

int	close_handler(t_scene *scene)
{
	mlx_destroy_image(scene->mlx_connection, scene->img.img_ptr);
	mlx_destroy_window(scene->mlx_connection, scene->mlx_window);
	mlx_destroy_display(scene->mlx_connection);
	free(scene->mlx_connection);
	exit(0);
}

int key_handler(int keysym, t_scene *scene)
{
	double	move_x;
	double	move_y;
	double	old_dir_x;

	move_x = scene->player.dir_x * scene->player.speed;
	move_y = scene->player.dir_y * scene->player.speed;

	if (keysym == XK_Escape)
		close_handler(scene);
	else if (keysym == XK_Up)
	{
		scene->player.pos_x += move_x;
		scene->player.pos_y += move_y;
	}
	else if (keysym == XK_Down)
	{
		scene->player.pos_x -= move_x;
		scene->player.pos_y -= move_y;
	}
	else if (keysym == XK_Left)
	{
		old_dir_x = scene->player.dir_x;
		scene->player.dir_x = old_dir_x * cos(-0.10) - scene->player.dir_y * sin(-0.10);
		scene->player.dir_y = old_dir_x * sin(-0.10) + scene->player.dir_y * cos(-0.10);
	}
	else if (keysym == XK_Right)
	{
		old_dir_x = scene->player.dir_x;
		scene->player.dir_x = old_dir_x * cos(0.10) - scene->player.dir_y * sin(0.10);
		scene->player.dir_y = old_dir_x * sin(0.10) + scene->player.dir_y * cos(0.10);
	}

	render_map(scene);
	DDA(scene,
	scene->player.pos_x + 15,
	scene->player.pos_y + 15,
	scene->player.pos_x + 15 + (scene->player.dir_x * 200),
	scene->player.pos_y + 15 + (scene->player.dir_y * 200));
	mlx_put_image_to_window(scene->mlx_connection, scene->mlx_window, scene->img.img_ptr, 0, 0);
	return (0);
}