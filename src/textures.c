#include "../cub3d.h"

uint32_t	get_pixel(mlx_texture_t *texture, int x, int y)
{
	uint8_t	*px;

	px = &texture->pixels[(y * texture->width + x) * 4];
	return (((uint32_t)px[0] << 24) | ((uint32_t)px[1] << 16)
		| ((uint32_t)px[2] << 8) | (uint32_t)px[3]);
}

mlx_texture_t	*select_texture(t_scene *scene)
{
	if (scene->ray.side == 0 && scene->ray.step_x > 0)
		return (scene->texture.wall_w);
	else if (scene->ray.side == 0 && scene->ray.step_x < 0)
		return (scene->texture.wall_e);
	else if (scene->ray.side == 1 && scene->ray.step_y > 0)
		return (scene->texture.wall_n);
	return (scene->texture.wall_s);
}
