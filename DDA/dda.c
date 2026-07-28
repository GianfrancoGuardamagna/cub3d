#include "../cub3d.h"

static void	init_ray(t_ray *ray, t_player *player, float fov_offset)
{
	ray->cell_w = WIDTH / MAP_WIDTH;
	ray->cell_h = HEIGHT / MAP_HEIGHT;
	ray->map_x = (int)(player->pos_x / ray->cell_w);
	ray->map_y = (int)(player->pos_y / ray->cell_h);
	ray->angle = atan2f(-player->dir_y, player->dir_x) * \
(180.0 / M_PI) + fov_offset;
	ray->dir_x = cos(ray->angle * (M_PI / 180));
	ray->dir_y = -sin(ray->angle * (M_PI / 180));
	if (ray->dir_x == 0)
		ray->delta_x = 1e30f;
	else
		ray->delta_x = (float)fabs(ray->cell_w / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_y = 1e30f;
	else
		ray->delta_y = (float)fabs(ray->cell_h / ray->dir_y);
}

//ray->step_x -> Steps in the map of cells
//ray->dist_x -> The distance between the player pos and the nearby border
static void	init_steps(t_ray *ray, t_player *player)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->dist_x = (player->pos_x - ray->map_x * \
ray->cell_w) / (float)fabs(ray->dir_x);
	}
	else
	{
		ray->step_x = 1;
		ray->dist_x = ((ray->map_x + 1) * ray->cell_w - \
player->pos_x) / (float)fabs(ray->dir_x);
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->dist_y = (player->pos_y - ray->map_y * \
ray->cell_h) / (float)fabs(ray->dir_y);
	}
	else
	{
		ray->step_y = 1;
		ray->dist_y = ((ray->map_y + 1) * ray->cell_h - \
player->pos_y) / (float)fabs(ray->dir_y);
	}
}

static float	march_ray(t_ray *ray, int **map)
{
	float	dist;

	while (1)
	{
		if (ray->dist_x < ray->dist_y)
		{
			dist = ray->dist_x;
			ray->dist_x += ray->delta_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			dist = ray->dist_y;
			ray->dist_y += ray->delta_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_x < 0 || ray->map_x >= MAP_WIDTH || \
ray->map_y < 0 || ray->map_y >= MAP_HEIGHT)
			return (-1);
		if (map[ray->map_y][ray->map_x] == 1)
			return (dist);
	}
}

static void	calc_wall_hit(t_ray *ray, t_player *player, float dist)
{
	if (ray->side == 0)
		ray->wall_x = (float)fmod(player->pos_y + dist * \
ray->dir_y, ray->cell_h) / ray->cell_h;
	else
		ray->wall_x = (float)fmod(player->pos_x + dist * \
ray->dir_x, ray->cell_w) / ray->cell_w;
	if (ray->wall_x < 0)
		ray->wall_x += 1.0f;
}

float	dda(t_scene *scene, float fov_offset)
{
	float	dist;

	init_ray(&scene->ray, &scene->player, fov_offset);
	init_steps(&scene->ray, &scene->player);
	dist = march_ray(&scene->ray, scene->map);
	if (dist < 0)
		return (-1);
	calc_wall_hit(&scene->ray, &scene->player, dist);
	return (dist);
}
