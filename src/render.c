#include "../cub3d.h"

static int	get_tex_x(t_scene *scene, mlx_texture_t *tex)
{
	int	tex_x;

	tex_x = (int)(scene->ray.wall_x * tex->width);
	if ((scene->ray.side == 0 && scene->ray.step_x < 0)
		|| (scene->ray.side == 1 && scene->ray.step_y > 0))
		tex_x = tex->width - 1 - tex_x;
	if (tex_x >= (int)tex->width)
		tex_x = tex->width - 1;
	if (tex_x < 0)
		tex_x = 0;
	return (tex_x);
}

static int	get_tex_y(mlx_texture_t *tex, int offset, int wall_height)
{
	int	tex_y;

	tex_y = (int)((float)offset / wall_height * tex->height);
	if (tex_y >= (int)tex->height)
		tex_y = tex->height - 1;
	if (tex_y < 0)
		tex_y = 0;
	return (tex_y);
}

static void	draw_vertical_line(t_scene *scene, int wall_height, int pos)
{
	mlx_texture_t	*tex;
	int				tex_x;
	int				top;
	int				y;

	tex = select_texture(scene);
	tex_x = get_tex_x(scene, tex);
	top = HEIGHT / 2 - wall_height / 2;
	y = 0;
	while (y < top && y < HEIGHT)
		mlx_put_pixel(scene->img, pos, y++, scene->ceiling.color);
	while (y < top + wall_height && y < HEIGHT)
	{
		mlx_put_pixel(scene->img, pos, y,
			get_pixel(tex, tex_x, get_tex_y(tex, y - top, wall_height)));
		y++;
	}
	while (y < HEIGHT)
		mlx_put_pixel(scene->img, pos, y++, scene->floor.color);
}

//distance = distance * cos(offset * M_PI / 180) -> avoids the fisheye effect
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
		if (distance > 0)
		{
			distance = distance * cos(offset * M_PI / 180);
			visual_height = HEIGHT / distance * CELL_SIZE;
			draw_vertical_line(scene, visual_height, x);
		}
		x++;
	}
}
