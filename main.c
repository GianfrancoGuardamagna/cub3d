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

int is_wall(t_scene *scene, int x, int y)
{
	int cell_width;
	int cell_height;

	cell_width = WIDTH / MAP_WIDTH;
	cell_height = HEIGHT / MAP_HEIGHT;

	if(scene->map[y / cell_height][x / cell_width] == 1)
		return 1;
	else
		return 0;
}

int check_walls_around(t_scene *scene, int x, int y)
{
	if (is_wall(scene, x + PLAYER_RADIUS, y + PLAYER_RADIUS))
		return (1);
	if (is_wall(scene, x - PLAYER_RADIUS, y - PLAYER_RADIUS))
		return (1);
	if (is_wall(scene, x + PLAYER_RADIUS, y - PLAYER_RADIUS))
		return (1);
	if (is_wall(scene, x - PLAYER_RADIUS, y + PLAYER_RADIUS))
		return (1);
	return (0);
}

static void	init_ray(t_ray *ray, t_player *player, float fov_offset)
{
	ray->cell_w = WIDTH / MAP_WIDTH;
	ray->cell_h = HEIGHT / MAP_HEIGHT;
	ray->map_x = (int)(player->pos_x / ray->cell_w);
	ray->map_y = (int)(player->pos_y / ray->cell_h);
	ray->angle = atan2f(-player->dir_y, player->dir_x) * (180.0 / M_PI) + fov_offset;
	ray->dir_x = cos(ray->angle * (M_PI / 180));
	ray->dir_y = -sin(ray->angle * (M_PI / 180));
	if(ray->dir_x == 0)
		ray->delta_x = 1e30f;
	else
		ray->delta_x = (float)fabs(ray->cell_w / ray->dir_x);
	if(ray->dir_y == 0)
		ray->delta_y = 1e30f;
	else
		ray->delta_y = (float)fabs(ray->cell_h / ray->dir_y);
}

static void	init_steps(t_ray *ray, t_player *player)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1; //Steps in the map of cells
		ray->dist_x = (player->pos_x - ray->map_x * ray->cell_w) / (float)fabs(ray->dir_x); //The distance between the player pos and the nearby border
	}
	else
	{
		ray->step_x = 1;
		ray->dist_x = ((ray->map_x + 1) * ray->cell_w - player->pos_x) / (float)fabs(ray->dir_x);
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->dist_y = (player->pos_y - ray->map_y * ray->cell_h) / (float)fabs(ray->dir_y);
	}
	else
	{
		ray->step_y = 1;
		ray->dist_y = ((ray->map_y + 1) * ray->cell_h - player->pos_y) / (float)fabs(ray->dir_y);
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
		if (ray->map_x < 0 || ray->map_x >= MAP_WIDTH || ray->map_y < 0 || ray->map_y >= MAP_HEIGHT)
			return (-1);
		if (map[ray->map_y][ray->map_x] == 1)
			return (dist);
	}
}

static void	calc_wall_hit(t_ray *ray, t_player *player, float dist)
{
	if (ray->side == 0)
		ray->wall_x = (float)fmod(player->pos_y + dist * ray->dir_y, ray->cell_h) / ray->cell_h;
	else
		ray->wall_x = (float)fmod(player->pos_x + dist * ray->dir_x, ray->cell_w) / ray->cell_w;
	if (ray->wall_x < 0)
		ray->wall_x += 1.0f;
}

float	DDA(t_scene *scene, float fov_offset)
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

/*void render_map(t_scene *scene)
{
	int y;
	int x;
	int cell_width;
	int cell_height;

	cell_width = WIDTH / MAP_WIDTH;
	cell_height = HEIGHT / MAP_HEIGHT;

	y = 0;
	while(y < HEIGHT)
	{
		x = 0;
		while(x < WIDTH)
		{
			if((y % cell_height) == 0) //GRID
				pixel_put(&scene->img, x, y, 0xffffffff);
			else if((x % cell_width) == 0) //GRID
				pixel_put(&scene->img, x, y, 0xffffffff);
			//else if((x >= scene->player.pos_x && x <= (scene->player.pos_x + 30)) && (y >= scene->player.pos_y && y <= (scene->player.pos_y + 30))) //PLAYER
			//{
				//render_ray(scene);
				//pixel_put(&scene->img, x, y, scene->player.color);
			//}
			else if((y % cell_height) != 0 || (x % cell_width) != 0) //WALLS
			{
				if(scene->map[y / cell_height][x / cell_width] == 1)
					pixel_put(&scene->img, x, y, 0xbcdbcdbc);
				else
					pixel_put(&scene->img, x, y, 0xabababab);
			}
			x++;
		}
		y++;
	}
}*/

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

void analize_fov(t_scene *scene)
{
	int		x;
	float	offset;
	float	distance;
	int		visual_height;

	x = 0;
	while (x < WIDTH)
	{
		offset = PLAYER_FOV / 2 - ((float)x / WIDTH) * PLAYER_FOV;
		if((distance = DDA(scene, offset)) <= 0)
		{
			x++;
			continue ;
		}
		distance = distance * cos(offset * M_PI / 180); //Modify value for avoiding fisheye
		visual_height = HEIGHT / distance * (WIDTH / MAP_WIDTH);
		draw_vertical_line(scene, visual_height, x);
		x++;
	}
}

int loading_struct(t_scene *scene)
{
	if(!(scene->mlx_connection = mlx_init(WIDTH, HEIGHT, "cub3D", true)))
		return 1;
//	scene->mlx_window = mlx_new_window(scene->mlx_connection, WIDTH, HEIGHT, "cub3d");
//	scene->img.img_ptr = mlx_new_image(scene->mlx_connection, WIDTH, HEIGHT);
//	scene->img.pixels_ptr = mlx_get_data_addr(scene->img.img_ptr, &scene->img.bpp, &scene->img.line_len, &scene->img.endian);

	if(!(scene->img = mlx_new_image(scene->mlx_connection, WIDTH, HEIGHT)))
		return 1;
	// scene->wall_N.img_ptr = mlx_xpm_file_to_image(scene->mlx_connection, "./assets/wall_N.xpm", &scene->wall_N.width, &scene->wall_N.height);
	// scene->wall_N.pixels_ptr = mlx_get_data_addr(scene->wall_N.img_ptr, &scene->wall_N.bpp, &scene->wall_N.line_len, &scene->wall_N.endian);
	// scene->wall_S.img_ptr = mlx_xpm_file_to_image(scene->mlx_connection, "./assets/wall_S.xpm", &scene->wall_S.width, &scene->wall_S.height);
	// scene->wall_S.pixels_ptr = mlx_get_data_addr(scene->wall_S.img_ptr, &scene->wall_S.bpp, &scene->wall_S.line_len, &scene->wall_S.endian);
	// scene->wall_E.img_ptr = mlx_xpm_file_to_image(scene->mlx_connection, "./assets/wall_E.xpm", &scene->wall_E.width, &scene->wall_E.height);
	// scene->wall_E.pixels_ptr = mlx_get_data_addr(scene->wall_E.img_ptr, &scene->wall_E.bpp, &scene->wall_E.line_len, &scene->wall_E.endian);
	// scene->wall_W.img_ptr = mlx_xpm_file_to_image(scene->mlx_connection, "./assets/wall_W.xpm", &scene->wall_W.width, &scene->wall_W.height);
	// scene->wall_W.pixels_ptr = mlx_get_data_addr(scene->wall_W.img_ptr, &scene->wall_W.bpp, &scene->wall_W.line_len, &scene->wall_W.endian);

	if(!(scene->texture.wall_N = mlx_load_png("./assets/wall_N.png")))
		return 1;
	if(!(scene->texture.wall_E = mlx_load_png("./assets/wall_E.png")))
		return 1;
	if(!(scene->texture.wall_S = mlx_load_png("./assets/wall_S.png")))
		return 1;
	if(!(scene->texture.wall_W = mlx_load_png("./assets/wall_W.png")))
		return 1;
	scene->floor.color = createRGB(220, 110, 0);
	scene->ceiling.color = createRGB(225, 30, 0);
	return 0;
}

int main(void)
{
	t_scene *scene;
	int map[MAP_WIDTH][MAP_HEIGHT] = 
	{
		{1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 1, 0, 0, 1},
		{1, 'N', 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1},
	};

	scene = malloc(sizeof(t_scene));
	if (!scene)
		return 1;

	//Falta mensajes de errores (mlx_errno)
	if(loading_struct(scene) != 0)
	{
		close_handler(scene);
		return 1;
	}

	//Falta mensajes de errores
	if(populate_map(scene, MAP_WIDTH, MAP_HEIGHT, map) != 0)
	{
		close_handler(scene);
		return 1;
	}

	initialize_player(scene);
	events_init(scene);
	analize_fov(scene);
	mlx_image_to_window(scene->mlx_connection, scene->img, 0, 0);
	mlx_loop(scene->mlx_connection);
	close_handler(scene);
	return 0;
}

//Double x Float, cambié libreria gráfica, comencé a controlar eficiencia y chequeo de errores, corregí texturas gráficas y bug de la wall collison agregando un player radius que colisiona antes que la camara