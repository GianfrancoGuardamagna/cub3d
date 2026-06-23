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
	int i;

	mlx_destroy_image(scene->mlx_connection, scene->img.img_ptr);
	mlx_destroy_window(scene->mlx_connection, scene->mlx_window);
	mlx_destroy_display(scene->mlx_connection);
	free(scene->mlx_connection);

	i = 0;
	while(i < MAP_HEIGHT)
	{
		free(scene->map[i]);
		i++;
	}
	free(scene->map);
	free(scene->wall);
	free(scene);
	exit(0);
}

int key_handler(int keysym, t_scene *scene)
{
	double	move_x;
	double	move_y;

	move_x = scene->player.dir_x * scene->player.speed;
	move_y = scene->player.dir_y * scene->player.speed;

	if (keysym == XK_Escape)
		close_handler(scene);
	else if (keysym == XK_w)
	{
		if(is_wall(scene, scene->player.pos_x + move_x, scene->player.pos_y + move_y))
			return (0);
		scene->player.pos_x += move_x;
		scene->player.pos_y += move_y;
	}
	else if (keysym == XK_s)
	{
		if(is_wall(scene, scene->player.pos_x - move_x, scene->player.pos_y - move_y))
			return (0);
		scene->player.pos_x -= move_x;
		scene->player.pos_y -= move_y;
	}
	else if (keysym == XK_Left)
	{
		scene->player.angle -= 1;
		scene->player.dir_x = cos(scene->player.angle * (3.14159 / 180));
		scene->player.dir_y = -sin(scene->player.angle * (3.14159 / 180));
		if(scene->player.angle < 0)
			scene->player.angle += 360;
	}
	else if (keysym == XK_Right)
	{
		scene->player.angle += 1;
		scene->player.dir_x = cos(scene->player.angle * (3.14159 / 180));
		scene->player.dir_y = -sin(scene->player.angle * (3.14159 / 180));
		if(scene->player.angle > 360)
			scene->player.angle -= 360;
	}

	draw_fov(scene);
	mlx_put_image_to_window(scene->mlx_connection, scene->mlx_window, scene->img.img_ptr, 0, 0);
	return (0);
}