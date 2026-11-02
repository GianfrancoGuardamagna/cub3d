#include "../cub3d.h"

void	moving_north(t_scene *scene, float move_x, float move_y)
{
	if (check_walls_around\
(scene, scene->player.pos_x + move_x, scene->player.pos_y + move_y))
		return ;
	scene->player.pos_x += move_x;
	scene->player.pos_y += move_y;
}

void	moving_south(t_scene *scene, float move_x, float move_y)
{
	if (check_walls_around\
(scene, scene->player.pos_x - move_x, scene->player.pos_y - move_y))
		return ;
	scene->player.pos_x -= move_x;
	scene->player.pos_y -= move_y;
}

void	moving_east(t_scene *scene, float right_x, float right_y)
{
	if (check_walls_around\
(scene, scene->player.pos_x + right_x, scene->player.pos_y + right_y))
		return ;
	scene->player.pos_x += right_x;
	scene->player.pos_y += right_y;
}

void	moving_west(t_scene *scene, float right_x, float right_y)
{
	if (check_walls_around\
(scene, scene->player.pos_x - right_x, scene->player.pos_y - right_y))
		return ;
	scene->player.pos_x -= right_x;
	scene->player.pos_y -= right_y;
}
