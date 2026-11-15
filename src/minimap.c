#include "../cub3d.h"

static int	mini_cell(t_scene *scene)
{
	int	cell;
	int	cell_y;

	cell = (WIDTH / 4) / scene->map.cols;
	cell_y = (HEIGHT / 4) / scene->map.rows;
	if (cell_y < cell)
		cell = cell_y;
	if (cell < 1)
		cell = 1;
	return (cell);
}

static void	draw_square(t_scene *scene, int cx, int cy, uint32_t color)
{
	int	size;
	int	i;
	int	j;
	int	px;
	int	py;

	size = mini_cell(scene);
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			px = MINI_MARGIN + cx * size + j;
			py = MINI_MARGIN + cy * size + i;
			if (px < WIDTH && py < HEIGHT)
				mlx_put_pixel(scene->img, px, py, color);
			j++;
		}
		i++;
	}
}

static void	draw_player(t_scene *scene, int cx, int cy)
{
	int	dx;
	int	dy;

	dy = -MINI_PLAYER_R;
	while (dy <= MINI_PLAYER_R)
	{
		dx = -MINI_PLAYER_R;
		while (dx <= MINI_PLAYER_R)
		{
			if (dx * dx + dy * dy <= MINI_PLAYER_R * MINI_PLAYER_R
				&& cx + dx >= 0 && cx + dx < WIDTH
				&& cy + dy >= 0 && cy + dy < HEIGHT)
				mlx_put_pixel(scene->img, cx + dx, cy + dy, MINI_PLAYER);
			dx++;
		}
		dy++;
	}
}

static void	draw_row(t_scene *scene, int y)
{
	char	c;
	int		x;

	x = 0;
	while (scene->map.grid[y][x] && scene->map.grid[y][x] != '\n')
	{
		c = scene->map.grid[y][x];
		if (c == '1')
			draw_square(scene, x, y, MINI_WALL);
		else if (c != ' ')
			draw_square(scene, x, y, MINI_FLOOR);
		x++;
	}
}

void	paint_mapcell(t_scene *scene)
{
	int	y;
	int	size;

	y = 0;
	while (scene->map.grid[y])
	{
		draw_row(scene, y);
		y++;
	}
	size = mini_cell(scene);
	draw_player(scene,
		MINI_MARGIN + (int)(scene->player.pos_x / CELL_SIZE * size),
		MINI_MARGIN + (int)(scene->player.pos_y / CELL_SIZE * size));
}
