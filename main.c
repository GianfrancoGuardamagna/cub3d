#include "cub3d.h"

//I modified the "mlx_texture_t" data type so it contains now {int x; int y}
static void	draw_vertical_line(t_scene *scene, int wall_height, int pos)
{
	int				y;
	int				center;
	mlx_texture_t	*texture;

	texture = malloc(sizeof(mlx_texture_t));
	if (!texture)
		error_call(scene, 4, "Failed to initialize texture");
	select_texture(scene, texture);
	center = HEIGHT / 2 - wall_height / 2;
	texture->x = (int)(scene->ray.wall_x * texture->width);
	if ((unsigned int)texture->x >= texture->width)
		texture->x = texture->width - 1;
	y = 0;
	while (y < center)
		mlx_put_pixel(scene->img, pos, y++, scene->ceiling.color);
	while (y < center + wall_height && y < HEIGHT)
	{
		texture->y = (int)(((float)(y - center) / wall_height) \
* texture->height);
		if ((unsigned int)texture->y >= texture->height)
			texture->y = texture->height - 1;
		mlx_put_pixel(scene->img, pos, y++, get_pixel(texture));
	}
	while (y < HEIGHT)
		mlx_put_pixel(scene->img, pos, y++, scene->floor.color);
	free(texture);
}

//distance = distance * cos(offset * M_PI / 180)
//Modified value for avoiding fisheye
void	analize_fov(t_scene *scene)
{
	int		x;
	float	offset;
	float	distance;
	int		visual_height;

	x = 0;
	while (x < WIDTH)
	{
		offset = PLAYER_FOV / 2 - ((float)x / WIDTH) * PLAYER_FOV;
		distance = dda(scene, offset);
		if (distance <= 0)
		{
			x++;
			continue ;
		}
		distance = distance * cos(offset * M_PI / 180);
		visual_height = HEIGHT / distance * (WIDTH / MAP_WIDTH);
		draw_vertical_line(scene, visual_height, x);
		x++;
	}
}

void	paint_mapcell(t_scene *scene)
{
	int	minimap_width;
	int	minimap_height;
	int	x;
	int	y;
	int	map_row_cell;
	int	map_col_cell;
	int	margin;

	margin = 20;
	minimap_width = WIDTH / 4; //valor limite de pixeles hasta los que se puede pintar
	minimap_height = HEIGHT / 4;

	x = margin;
	while(x < minimap_width + margin)
	{
		y = margin;
		map_row_cell = ((x - margin) * MAP_WIDTH - 1) / minimap_width;
		while(y < minimap_height + margin)
		{
			map_col_cell = ((y - margin) * MAP_HEIGHT - 1) / minimap_height;
			if(scene->map[map_col_cell][map_row_cell] == 1)
				mlx_put_pixel(scene->img, x, y, 1294967285);
			else if(scene->map[map_col_cell][map_row_cell] == 0)
				mlx_put_pixel(scene->img, x, y, 3294967285);
			else
				mlx_put_pixel(scene->img, x, y, 2294967285);
			y++;
		}
		x++;
	}
}

int	main(void)
{
	t_scene	*scene;

	scene = malloc(sizeof(t_scene));
	if (!scene)
		error_call(NULL, 0, "42");
	init_scene(scene);
	init_player(scene);
	init_events(scene);
	analize_fov(scene);
	paint_mapcell(scene);
	mlx_image_to_window(scene->mlx_connection, scene->img, 0, 0);
	mlx_loop(scene->mlx_connection);
	close_handler(scene);
	return (0);
}
