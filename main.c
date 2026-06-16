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

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return;

	offset = (y * img->line_len) + (x * (img->bpp / 8));
	*(unsigned int *)(img->pixels_ptr + offset) = color;
}

int abs(int n)
{
	if(n > 0)
		return n;
	else
		return n * -1;
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
			x++;
		}
		y++;
	}
}

void render_ray(t_scene *scene)
{
	int i;

	i = 0;
	while(i <= 100)
	{
		pixel_put(&scene->img, scene->player.pos_x + 15, scene->player.pos_y - i, scene->player.color);
		i++;
	}
}

void DDA(t_scene *scene, int X0, int Y0, int X1, int Y1)
{
	int i;
	int dx;
	int dy;
	int steps;
	float Xinc;
	float Yinc;
	float X;
	float Y;

	// calculate dx & dy
	dx = X1 - X0;
	dy = Y1 - Y0;

	// calculate steps required for generating pixels
	if(abs(dx) > abs(dy))
		steps = abs(dx);
	else
		steps = abs(dy);

	// calculate increment in x & y for each steps
	Xinc = dx / (float)steps;
	Yinc = dy / (float)steps;

	// Put pixel for each step
	X = X0;
	Y = Y0;
	i = 0;
	while(i <= steps)
	{
		pixel_put(&scene->img, round(X), round(Y), 0xffffffff);
		X += Xinc;
		Y += Yinc;
		i++;
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
			else if((x >= scene->player.pos_x && x <= (scene->player.pos_x + 30)) && (y >= scene->player.pos_y && y <= (scene->player.pos_y + 30))) //PLAYER
			{
				//render_ray(scene);
				pixel_put(&scene->img, x, y, scene->player.color);
			}
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

void calculate_player_position(t_scene *scene)
{
	int cell_width;
	int cell_height;
	int i;
	int j;

	cell_width = WIDTH / MAP_WIDTH;
	cell_height = HEIGHT / MAP_HEIGHT;
	i = 0;
	while(i < MAP_HEIGHT)
	{
		j = 0;
		while(j < MAP_WIDTH)
		{
			if(scene->map[i][j] == 'N')
			{
				scene->player.pos_x = (WIDTH / (j + 1)) + (cell_width / 2);
				scene->player.pos_y = (HEIGHT / (i + 1)) + (cell_height / 2);
				scene->player.dir_x = 0;
				scene->player.dir_y = -1;
			}
			else if(scene->map[i][j] == 'S')
			{
				scene->player.pos_x = (WIDTH / (j + 1)) + (cell_width / 2);
				scene->player.pos_y = (HEIGHT / (i + 1)) + (cell_height / 2);
				scene->player.dir_x = 0;
				scene->player.dir_y = 1;
			}
			else if(scene->map[i][j] == 'W')
			{
				scene->player.pos_x = (WIDTH / (j + 1)) + (cell_width / 2);
				scene->player.pos_y = (HEIGHT / (i + 1)) + (cell_height / 2);
				scene->player.dir_x = -1;
				scene->player.dir_y = 0;
			}
			else if(scene->map[i][j] == 'E')
			{
				scene->player.pos_x = (WIDTH / (j + 1)) + (cell_width / 2);
				scene->player.pos_y = (HEIGHT / (i + 1)) + (cell_height / 2);
				scene->player.dir_x = 1;
				scene->player.dir_y = 0;
			}
			j++;
		}
		i++;
	}
}

//Falta manejar el error de malloc
void populate_map(t_scene *scene, int map_width, int map_height, int map[][5])
{
	int i;
	int j;

	scene->map = malloc(sizeof(int *) * map_height);
	if(!scene->map)
		return ;

	i = 0;
	while(i < map_height)
	{
		j = 0;
		scene->map[i] = malloc(sizeof(int) * map_width);
		while(j < map_width)
		{
			scene->map[i][j] = map[i][j];
			j++;
		}
		i++;
	}
}

int main(void)
{
	t_scene *scene;
	int map[5][5] = 
	{
		{1, 1, 1, 1, 1},
		{1, 0, 1, 'N', 1},
		{1, 0, 0, 0, 1},
		{1, 0, 0, 1, 1},
		{1, 1, 1, 1, 1}
	};

	scene = malloc(sizeof(t_scene));
	if (!scene)
		return 1;

	scene->mlx_connection = mlx_init();
	scene->mlx_window = mlx_new_window(scene->mlx_connection, WIDTH, HEIGHT, "cub3d");
	scene->img.img_ptr = mlx_new_image(scene->mlx_connection, WIDTH, HEIGHT);
	scene->img.pixels_ptr = mlx_get_data_addr(scene->img.img_ptr, &scene->img.bpp, &scene->img.line_len, &scene->img.endian);

	scene->floor.color = createRGB(220, 110, 0);
	scene->ceiling.color = createRGB(225, 30, 0);

	populate_map(scene, MAP_WIDTH, MAP_HEIGHT, map);
	calculate_player_position(scene);
//	scene->player.pos_x = 100.0; //PRIMERO DIVIDIR LA VENTANA EN CELDAS Y LUEGO SE LE ASIGNA LA POSICION AL JUGADOR CORRESPONDIENTE, EN EL CENTRO DE LA CELDA CON LA ORIENTACIÓN DADA, PERO PRIMERO HAY QUE PROCESAR EL MAPA
//	scene->player.pos_y = 200.0;
//	scene->player.dir_x = 0.0;
//	scene->player.dir_y = -1.0;
	scene->player.speed = 10;
	scene->player.color = 0xffffffff;

	
	render_map(scene);
	//	render_floor(scene);
	//	render_ceiling(scene);
	//	render_player(scene);
	DDA(scene, scene->player.pos_x, scene->player.pos_y, scene->player.dir_x, scene->player.dir_y);
	events_init(scene);
	mlx_put_image_to_window(scene->mlx_connection, scene->mlx_window, scene->img.img_ptr, 0, 0);
	mlx_loop(scene->mlx_connection);
	scene_cleanup(scene);
	return 0;
}