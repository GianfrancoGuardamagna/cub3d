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

int DDA(t_scene *scene, int X0, int Y0, int X1, int Y1)
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

	// calculate increment in x & y for each steps, this is the slop or the hypotenus
	Xinc = dx / (float)steps;
	Yinc = dy / (float)steps;

	// Put pixel for each step
	X = X0;
	Y = Y0;
	i = 0;
	while(i <= steps)
	{
		if(is_wall(scene, round(X), round(Y)))
			break;
		//pixel_put(&scene->img, round(X), round(Y), 0xFF00FF);
		X += Xinc;
		Y += Yinc;
		i++;
	}

	return i;
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

//DEBERIA PINTAR CIELO ANTES DE LA LINEA Y SUELO DESPUES
void draw_vertical_line(t_scene *scene, int height, int pos, unsigned long color)
{
	int x;
	int y;

	x = 0;
	while(x < WIDTH)
	{
		if(x == pos)
		{
			y = HEIGHT / 2 - height / 2;
			//while(y < height && y < HEIGHT)
			while(y < height && y < HEIGHT)
			{
				pixel_put(&scene->img, x, y, color);
				y++;
			}
		}
		x++;
	}
}

void draw_fov(t_scene *scene)
{
	double scale;
	double offset;
	double angle;
	int distance;
	int visual_height;
	int x_line;
	int inc;

	scale = WIDTH / PLAYER_FOV; //FACTOR PARA QUE EL FOV SE ESCALA PARA QUE SEA EL WIDTH DE LA VENTANA
	offset = scene->player.angle - (PLAYER_FOV/2); //LE RESTA LA MITAD DEL CONO DE VISION PARA COMPRENDER LOS VALORES CORRESPONDIENTES AL CONO, SI MIRO A LOS 90 Y LE RESTO 30 COMIENZO A MIRAR DESDE LOS 60 (HASTA LOS 120)
	angle = scene->player.angle / (PLAYER_FOV/2); //??

	inc = PLAYER_FOV;
	while(angle <= (scene->player.angle + PLAYER_FOV))
	{
		distance = DDA(
					scene,
					scene->player.pos_x,
					scene->player.pos_y,
					scene->player.pos_x + (scene->player.dir_x * 200) + inc,
					scene->player.pos_y + (scene->player.dir_y * 200) + inc
					);

		if(distance <= 0)
			continue ;

		visual_height = (HEIGHT/distance) * 50; //MIENTRAS MAS CERCA ESTOY, visual_height SE ACERCA A HEIGHT, COMO LA DISTANCIA ES EN PIXELES HAY QUE ESCALARLA UN POCO
		x_line = (angle - offset) * scale;

		draw_vertical_line(scene, visual_height, x_line, 0xffffffff);
		angle += 0.5;
		inc -= 1;
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
	scene->player.speed = 10;
	scene->player.color = 0xffffffff;

	//render_map(scene);
	/*DDA(scene,
	scene->player.pos_x,
	scene->player.pos_y,
	scene->player.pos_x + (scene->player.dir_x * 200),
	scene->player.pos_y + (scene->player.dir_y * 200));*/
	draw_fov(scene);
	events_init(scene);

	mlx_put_image_to_window(scene->mlx_connection, scene->mlx_window, scene->img.img_ptr, 0, 0);
	mlx_loop(scene->mlx_connection);
	scene_cleanup(scene);
	return 0;
}