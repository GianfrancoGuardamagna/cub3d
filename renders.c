#include "cub3d.h"

void render_floor(t_scene *scene)
{
	int x;
	double y;

	y = HEIGHT / 1.5;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			pixel_put(&scene->img, x, (int) y, scene->floor.color);
			x++;
		}
		y++;
	}
}

void render_ceiling(t_scene *scene)
{
	int x;
	double y;

	y = 0;
	while (y < (HEIGHT / 3))
	{
		x = 0;
		while (x < WIDTH)
		{
			pixel_put(&scene->img, x, (int) y, scene->ceiling.color);
			x++;
		}
		y++;
	}
}

void render_player(t_scene *scene)
{
	int y;
	int x;

	y = 0;
	while(y < HEIGHT)
	{
		x = 0;
		while(x < WIDTH)
		{
			if((x >= scene->player.pos_x && x <= (scene->player.pos_x + 30)) && (y >= scene->player.pos_y && y <= (scene->player.pos_y + 30)))
			{
				pixel_put(&scene->img, x, y, scene->player.color);
			}
			x++;
		}
		y++;
	}
}

void render_ray(t_scene *scene)
{
	int i;

	i = 0;
	while(i <= 100)
	{
		pixel_put(&scene->img, scene->player.pos_x + 15, scene->player.pos_y - i, scene->player.color);
		i++;
	}
}
