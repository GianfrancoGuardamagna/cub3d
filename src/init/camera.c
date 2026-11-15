#include "../../cub3d.h"

void	rotate_player(t_scene *scene, double angle)
{
	t_player	*p;
	float		old_dir_x;

	p = &scene->player;
	old_dir_x = p->dir_x;
	p->dir_x = old_dir_x * cos(angle) - p->dir_y * sin(angle);
	p->dir_y = old_dir_x * sin(angle) + p->dir_y * cos(angle);
}

void	handle_camera_keys(t_scene *scene)
{
	if (mlx_is_key_down(scene->mlx_connection, MLX_KEY_LEFT))
		rotate_player(scene, -ROT_SPEED);
	if (mlx_is_key_down(scene->mlx_connection, MLX_KEY_RIGHT))
		rotate_player(scene, ROT_SPEED);
}

void	handle_camera_mouse(double xpos, double ypos, void *param)
{
	t_scene	*scene;
	double	delta_x;

	(void)ypos;
	scene = param;
	if (scene->camera != 1)
	{
		scene->last_mouse_x = xpos;
		return ;
	}
	delta_x = xpos - scene->last_mouse_x;
	scene->last_mouse_x = xpos;
	rotate_player(scene, delta_x * MOUSE_SENS);
}

