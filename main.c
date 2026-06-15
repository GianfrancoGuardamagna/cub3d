#include "cub3d.h"

unsigned long createRGB(int r, int g, int b)
{
	if(r > 255 || g > 255 || b > 255)
		return 0;
	return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

void	pixel_put(t_img *img, int x, int y, int color)
{
	int	offset;

	offset = (y * img->line_len) + (x * (img->bpp / 8));
	*(unsigned int *)(img->pixels_ptr + offset) = color;
}

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
			else
				pixel_put(&scene->img, x, y, 0x00000000);
			x++;
		}
		y++;
	}
}

//El map habria que maloquearlo en el main y pasarlo como int **
//El map deberia estar en la estructura de scene para poder pasarlo a los eventos sin problema
void render_map(t_scene *scene, int map_width, int map_height, int map[][5])
{
	int y;
	int x;
	int cell_width;
	int cell_height;
	(void) map;

	cell_width = WIDTH / map_width;
	cell_height = HEIGHT / map_height;

	y = 0;
	while(y < HEIGHT)
	{
		x = 0;
		while(x < WIDTH)
		{
			if((y % cell_height) == 0 || (x % cell_width) == 0)
				pixel_put(&scene->img, x, y, scene->player.color);
			x++;
		}
		y++;
	}
}

int main(void)
{
	t_scene *scene;
	int map[5][5] = 
	{
		{1, 1, 1, 1, 1},
		{1, 0, 1, 2, 1},
		{1, 0, 0, 0, 1},
		{1, 0, 0, 1, 1},
		{1, 1, 1, 1, 1}
	};

	(void) map;

	scene = malloc(sizeof(t_scene));
	if (!scene)
		return 1;

	scene->mlx_connection = mlx_init();
	scene->mlx_window = mlx_new_window(scene->mlx_connection, WIDTH, HEIGHT, "cub3d");
	scene->img.img_ptr = mlx_new_image(scene->mlx_connection, WIDTH, HEIGHT);
	scene->img.pixels_ptr = mlx_get_data_addr(scene->img.img_ptr, &scene->img.bpp, &scene->img.line_len, &scene->img.endian);

	scene->floor.color = createRGB(220, 110, 0);
	scene->ceiling.color = createRGB(225, 30, 0);

	scene->player.pos_x = 100.0;
	scene->player.pos_y = 200.0;
	scene->player.dir_x = 0.0;
	scene->player.dir_y = -1.0;
	scene->player.speed = 10;
	scene->player.color = 0xffffffff;

	events_init(scene);

//	render_map(scene, 5, 5, map);
//	render_floor(scene);
//	render_ceiling(scene);
	render_player(scene);
	mlx_put_image_to_window(scene->mlx_connection, scene->mlx_window, scene->img.img_ptr, 0, 0);
	mlx_loop(scene->mlx_connection);
	scene_cleanup(scene);
	return 0;
}