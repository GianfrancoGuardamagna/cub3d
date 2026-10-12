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

// !FUNCION MINIMAPA
/* void	draw_player(t_scene *scene, float x, float y)
{
	int radius;
	int dx;
	int dy;
	int cx;
	int cy;
	int px;
	int py;

	radius = 4;
	cx = (int)x;
	cy = (int)y;
	dy = -radius;
	while (dy <= radius)
	{
		dx = -radius;
		while (dx <= radius)
		{
			if (dx * dx + dy * dy <= radius * radius)
			{
				px = cx + dx;
				py = cy + dy;
				if (px >= 0 && px < (int)scene->img->width
					&& py >= 0 && py < (int)scene->img->height)
					mlx_put_pixel(scene->img, px, py, 1595523219);
			}
			dx++;
		}
		dy++;
	}
} */
// !FUNCION MINIMAPA
/* void	paint_mapcell(t_scene *scene)
{
	int	minimap_width;
	int	minimap_height;
	int	x;
	int	y;
	int	map_row_cell;
	int	map_col_cell;
	int	margin;
	float	pixel_x;
	float	pixel_y;

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
			else
				mlx_put_pixel(scene->img, x, y, 3294967285);
			y++;
		}
		x++;
	}
	pixel_x = margin + (scene->player.pos_x / (WIDTH / MAP_WIDTH) / MAP_WIDTH) * minimap_width;
	pixel_y = margin + (scene->player.pos_y / (HEIGHT / MAP_HEIGHT) / MAP_HEIGHT) * minimap_height;
	draw_player(scene, pixel_x, pixel_y);
} */

int	main(int ac, char **av)
{
	t_scene	*scene;
	(void)av;

	if (ac != 2)
	{
		ft_fprintf(2, "Invalid number of av. Ej: ./cub3d map.cub\n");
		return (0);
	}
	if (check_extension(av[1]) == 0)
	{
		printf("llego2\n");
		scene = ft_calloc(1, sizeof(t_scene));
		if (!scene)
			error_call(NULL, 0, "42");
		/* 	init_scene(scene);
		init_player(scene);
		init_events(scene);
		analize_fov(scene);
		paint_mapcell(scene);
		mlx_image_to_window(scene->mlx_connection, scene->img, 0, 0);
		mlx_loop(scene->mlx_connection); */
		close_handler(scene);
	}
	return (0);
}
