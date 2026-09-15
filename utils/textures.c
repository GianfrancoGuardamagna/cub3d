#include "../cub3d.h"

uint32_t	get_pixel(mlx_texture_t *texture)
{
	//! COMENTO FUNCION PARA PODER PARSEAR TRANQUILAMENTE
	(void)texture;
	return (0);
/* 	int	i;

	i = (texture->y * texture->width + texture->x) * 4;
	return (
		(texture->pixels[i] << 24)
		| (texture->pixels[i + 1] << 16)
		| (texture->pixels[i + 2] << 8)
		| texture->pixels[i + 3]
	); */
}

void	select_texture(t_scene *scene, mlx_texture_t *texture)
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
