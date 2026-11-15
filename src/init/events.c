#include "../../cub3d.h"

static void	drink_animation(void)
{
	write(1, "matecito\n", 9);
}

static void	toggle_mouse(t_scene *scene)
{
	int32_t	mx;
	int32_t	my;

	scene->camera *= -1;
	if (scene->camera == 1)
	{
		mlx_set_cursor_mode(scene->mlx_connection, MLX_MOUSE_DISABLED);
		mlx_get_mouse_pos(scene->mlx_connection, &mx, &my);
		scene->last_mouse_x = mx;
	}
	else
		mlx_set_cursor_mode(scene->mlx_connection, MLX_MOUSE_NORMAL);
}

void	handle_key_event(mlx_key_data_t keydata, void *param)
{
	t_scene	*scene;

	scene = param;
	if (keydata.action != MLX_PRESS)
		return ;
	if (keydata.key == MLX_KEY_C)
		toggle_mouse(scene);
	if (keydata.key == MLX_KEY_M)
		drink_animation();
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(scene->mlx_connection);
}
