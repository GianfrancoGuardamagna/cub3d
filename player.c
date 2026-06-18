#include "cub3d.h"

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
				scene->player.angle = 90;
			}
			else if(scene->map[i][j] == 'S')
			{
				scene->player.pos_x = (WIDTH / (j + 1)) + (cell_width / 2);
				scene->player.pos_y = (HEIGHT / (i + 1)) + (cell_height / 2);
				scene->player.dir_x = 0;
				scene->player.dir_y = 1;
				scene->player.angle = 270;
			}
			else if(scene->map[i][j] == 'W')
			{
				scene->player.pos_x = (WIDTH / (j + 1)) + (cell_width / 2);
				scene->player.pos_y = (HEIGHT / (i + 1)) + (cell_height / 2);
				scene->player.dir_x = -1;
				scene->player.dir_y = 0;
				scene->player.angle = 180;
			}
			else if(scene->map[i][j] == 'E')
			{
				scene->player.pos_x = (WIDTH / (j + 1)) + (cell_width / 2);
				scene->player.pos_y = (HEIGHT / (i + 1)) + (cell_height / 2);
				scene->player.dir_x = 1;
				scene->player.dir_y = 0;
				scene->player.angle = 0;
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
