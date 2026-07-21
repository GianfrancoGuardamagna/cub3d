#include "cub3d.h"

uint32_t	get_pixel(mlx_texture_t *texture)
{
	int	i;

	i = (texture->y * texture->width + texture->x) * 4;
	return (
		(texture->pixels[i] << 24)
		| (texture->pixels[i + 1] << 16)
		| (texture->pixels[i + 2] << 8)
		| texture->pixels[i + 3]
	);
}

void select_texture(t_scene *scene, mlx_texture_t *texture)
{
	if (scene->ray.side == 0 && scene->ray.step_x > 0)
		*texture = *scene->texture.wall_W;
	else if (scene->ray.side == 0 && scene->ray.step_x < 0)
		*texture = *scene->texture.wall_E;
	else if (scene->ray.side == 1 && scene->ray.step_y > 0)
		*texture = *scene->texture.wall_N;
	else
		*texture = *scene->texture.wall_S;
}

void draw_vertical_line(t_scene *scene, int wall_height, int pos)
{
	int				y;
	int				center;
	mlx_texture_t	*texture;
//	int				offset;
//	unsigned int	color;

	//Falta gestionar si falla memoria
	texture = malloc(sizeof(mlx_texture_t));
	if(!texture)
		return ;

	select_texture(scene, texture);
	center = HEIGHT / 2 - wall_height / 2;

	//I modified the "mlx_texture_t" data type so it contains now {int x; int y}
	//En que situaciones se da este error?
	texture->x = (int)(scene->ray.wall_x * texture->width);
	if ((unsigned int)texture->x >= texture->width)
		texture->x = texture->width - 1;

	y = 0;
	while (y < center)
		mlx_put_pixel(scene->img, pos, y++, scene->ceiling.color);
	while (y < center + wall_height && y < HEIGHT)
	{
		texture->y = (int)(((float)(y - center) / wall_height) * texture->height);
		if ((unsigned int)texture->y >= texture->height)
			texture->y = texture->height - 1;
//		offset = (texture->y * texture->width) + (texture->x * (texture->bytes_per_pixel / 8));
//		color = *(unsigned int *)(scene->wall.pixels_ptr + offset);
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
		if ((distance = dda(scene, offset)) <= 0)
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

int main(void)
{
	t_scene *scene;

	scene = init_scene(&scene);
	init_player(scene);
	init_events(scene);
	analize_fov(scene);
	//HASTA AQUI LLEGO LA REFACTORIZACION Y FORMATEO
	mlx_image_to_window(scene->mlx_connection, scene->img, 0, 0);
	mlx_loop(scene->mlx_connection);
	close_handler(scene);
	return 0;
}
