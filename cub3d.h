#include "minilibx-linux/mlx.h"
#include <math.h>
#include <X11/X.h>
#include <X11/keysym.h>
#include <stdlib.h>
#include <stdio.h> //ELIMINAR
#include <unistd.h> //ELIMINAR

#ifndef WIDTH
#define WIDTH 300
#endif
#ifndef HEIGHT
#define HEIGHT 200
#endif
#ifndef CELL_SIZE
#define CELL_SIZE 10
#endif
#ifndef MAP_WIDTH
#define MAP_WIDTH 5
#endif
#ifndef MAP_HEIGHT
#define MAP_HEIGHT 5
#endif
#ifndef PLAYER_FOV
#define PLAYER_FOV 60
#endif
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	angle;
	double	speed;
	unsigned long color;
}	t_player;

typedef struct s_floor
{
	int	r;
	int	g;
	int	b;
	unsigned long color;
}	t_floor;

typedef struct s_ceiling
{
	int	r;
	int	g;
	int	b;
	unsigned long color;
}	t_ceiling;

typedef struct s_img
{
	void	*img_ptr;
	char	*pixels_ptr;
	int		bpp;
	int		endian;
	int		line_len;
}	t_img;

typedef struct s_scene
{
	void	*mlx_connection;
	void	*mlx_window;
	t_img	img;
	t_ceiling ceiling;
	t_floor floor;
	t_player player;
	int **map;
}	t_scene;

//MAIN?
void render_map(t_scene *scene);
int DDA(t_scene *scene, int X0, int Y0, int X1, int Y1);
void draw_fov(t_scene *scene);

//EVENTS
void	scene_cleanup(t_scene *scene);
void	events_init(t_scene *scene);
int		close_handler(t_scene *scene);
int		key_handler(int keysym, t_scene *scene);

//RENDERS
void render_floor(t_scene *scene);
void render_ceiling(t_scene *scene);
void render_player(t_scene *scene);
void render_ray(t_scene *scene);

//AUX
int abs(int n); //NO ESTÁ EN MATH.H?
void	pixel_put(t_img *img, int x, int y, int color);
unsigned long createRGB(int r, int g, int b);
double calcular_angulo_grados(double x0, double y0, double x1, double y1);

//PLAYER
void calculate_player_position(t_scene *scene);
void populate_map(t_scene *scene, int map_width, int map_height, int map[][5]);