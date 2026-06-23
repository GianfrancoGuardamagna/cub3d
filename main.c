#include "cub3d.h"

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

double DDA(t_scene *scene, double pos_x, double pos_y, double dir_x, double dir_y)
{
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	double	cell_width;
	double	cell_height;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	double	dist;

	cell_width = (double)WIDTH / MAP_WIDTH;
	cell_height = (double)HEIGHT / MAP_HEIGHT;
	map_x = (int)(pos_x / cell_width);
	map_y = (int)(pos_y / cell_height);

	if (dir_x == 0)
		delta_dist_x = 1e30; //Numero gigante: nunca va a cruzar un borde vertical
	else
		delta_dist_x = fabs(cell_width / dir_x);
	if (dir_y == 0)
		delta_dist_y = 1e30;
	else
		delta_dist_y = fabs(cell_height / dir_y);

	if (dir_x < 0)
	{
		step_x = -1;
		side_dist_x = (pos_x - map_x * cell_width) / fabs(dir_x);
	}
	else
	{
		step_x = 1;
		side_dist_x = ((map_x + 1) * cell_width - pos_x) / fabs(dir_x);
	}
	if (dir_y < 0)
	{
		step_y = -1;
		side_dist_y = (pos_y - map_y * cell_height) / fabs(dir_y);
	}
	else
	{
		step_y = 1;
		side_dist_y = ((map_y + 1) * cell_height - pos_y) / fabs(dir_y);
	}

	while (1)
	{
		if (side_dist_x < side_dist_y)
		{
			dist = side_dist_x;
			side_dist_x += delta_dist_x;
			map_x += step_x;
		}
		else
		{
			dist = side_dist_y;
			side_dist_y += delta_dist_y;
			map_y += step_y;
		}
		if (map_x < 0 || map_x >= MAP_WIDTH || map_y < 0 || map_y >= MAP_HEIGHT)
			return (-1);
		if (scene->map[map_y][map_x] == 1)
			return (dist);
	}
}

//El map habria que maloquearlo en el main y pasarlo como int **
//El map deberia estar en la estructura de scene para poder pasarlo a los eventos sin problema
void render_map(t_scene *scene)
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
}

void draw_vertical_line(t_scene *scene, int height, int pos, unsigned long color)
{
	int y;
	int center;

	y = 0;
	center = HEIGHT / 2 - height / 2; // Marca el comienzo de la pared
	while(y < center) //CEILING
	{
		pixel_put(&scene->img, pos, y, scene->ceiling.color);
		y++;
	}
	y = center;
	while(y < center + height && y < HEIGHT) //WALL
	{
		pixel_put(&scene->img, pos, y, color);
		y++;
	}
	while(y < HEIGHT) //FLOOR
	{
		pixel_put(&scene->img, pos, y, scene->floor.color);
		y++;
	}
}

void draw_fov(t_scene *scene)
{
	int x;
	double offset;
	double angle;
	double dir_x;
	double dir_y;
	double distance;
	int visual_height;

	x = 0;
	while(x < WIDTH) //Itero por el eje X
	{
		offset = -PLAYER_FOV/2 + ((double)x / WIDTH) * PLAYER_FOV; //Calculo el desfasaje de la columna con respecto a mi POV
		angle = scene->player.angle + offset; //Calculo el angulo entonces
		dir_x = cos(angle * (3.14159 / 180)); //Calculo la posicion de X trasnformando los angulos euclidianos en radianes
		dir_y = -sin(angle * (3.14159 / 180));
		distance = DDA(scene, scene->player.pos_x, scene->player.pos_y, dir_x, dir_y);
		
		if(distance <= 0)
		{
			x++;
			continue ;
		}

		distance = distance * cos(offset * 3.14159 / 180); //Compensa la distancia con el angulo, ya que los rayos que salen en linea recta recorreran menos camino que los que están en el borde del cono de vision y entonces generará un efecto ojo de pez
		visual_height = ((double) HEIGHT/distance) * 50; //MIENTRAS MAS CERCA ESTOY, visual_height SE ACERCA A HEIGHT, COMO LA DISTANCIA ES EN PIXELES HAY QUE ESCALARLA UN POCO
		draw_vertical_line(scene, visual_height, x, 0xffffffff);
		x++;
	}
}

int main(void)
{
	t_scene *scene;
	int map[5][5] = 
	{
		{1, 1, 1, 1, 1},
		{1, 0, 0, 0, 1},
		{1, 0, 1, 0, 1},
		{1, 'N', 0, 0, 1},
		{1, 1, 1, 1, 1}
	};

	scene = malloc(sizeof(t_scene));
	if (!scene)
		return 1;

	scene->mlx_connection = mlx_init();
	scene->mlx_window = mlx_new_window(scene->mlx_connection, WIDTH, HEIGHT, "cub3d");
	scene->img.img_ptr = mlx_new_image(scene->mlx_connection, WIDTH, HEIGHT);
	scene->img.pixels_ptr = mlx_get_data_addr(scene->img.img_ptr, &scene->img.bpp, &scene->img.line_len, &scene->img.endian);

	scene->wall = mlx_xpm_file_to_image(scene->mlx_connection, "./assets/wall_texture.xpm", 500, 500);
	scene->floor.color = createRGB(220, 110, 0);
	scene->ceiling.color = createRGB(225, 30, 0);

	populate_map(scene, MAP_WIDTH, MAP_HEIGHT, map);
	calculate_player_position(scene);
	scene->player.speed = 10;

	draw_fov(scene);
	events_init(scene);

	mlx_put_image_to_window(scene->mlx_connection, scene->mlx_window, scene->img.img_ptr, 0, 0);
	mlx_loop(scene->mlx_connection);
	scene_cleanup(scene);
	return 0;
}