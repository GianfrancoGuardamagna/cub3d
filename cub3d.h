#include "MLX42/include/MLX42/MLX42.h"
#include <math.h>
#include <X11/X.h>
#include <X11/keysym.h>
#include <stdlib.h>
#include <stdio.h> //ELIMINAR
#include <unistd.h> //ELIMINAR

#ifndef WIDTH
#define WIDTH 900
#endif
#ifndef HEIGHT
#define HEIGHT 600
#endif
//#ifndef CELL_SIZE
//#define CELL_SIZE 10
//#endif
#ifndef MAP_WIDTH
#define MAP_WIDTH 7
#endif
#ifndef MAP_HEIGHT
#define MAP_HEIGHT 7
#endif
#ifndef PLAYER_FOV
#define PLAYER_FOV 60
#endif
#ifndef PLAYER_RADIUS
#define PLAYER_RADIUS 15
#endif
#ifndef M_PI
#define M_PI 3.1415
#endif

typedef struct s_player
{
	float	pos_x;
	float	pos_y;
	float	dir_x;
	float	dir_y;
	int		speed;
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
	int		width;
	int		height;
}	t_img;

typedef struct s_ray
{
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		side;
	int		cell_w;
	int		cell_h;
	float	angle;
	float	dir_x;
	float	dir_y;
	float	dist_x;
	float	dist_y;
	float	delta_x;
	float	delta_y;
	float	wall_x;
}	t_ray;

typedef struct s_texture
{
	mlx_texture_t *wall_N;
	mlx_texture_t *wall_E;
	mlx_texture_t *wall_S;
	mlx_texture_t *wall_W;
}	t_texture;

typedef struct s_scene
{
	void	*mlx_connection;
//	void	*mlx_window;
//	t_img	img;
	mlx_image_t *img;
	t_ceiling ceiling;
	t_floor floor;
	t_player player;
	t_ray ray;
	int **map;
//	t_img wall;
//	t_img wall_N;
//	t_img wall_E;
//	t_img wall_S;
//	t_img wall_W;
//	mlx_texture_t *wall;
	t_texture texture;
}	t_scene;

//MAIN
void	render_map(t_scene *scene);
float	DDA(t_scene *scene, float fov_offset);
void	analize_fov(t_scene *scene);
int		check_walls_around(t_scene *scene, int x, int y);
int		is_wall(t_scene *scene, int x, int y);

//EVENTS
void	events_init(t_scene *scene);
void	close_handler(void* param);
void	key_handler(mlx_key_data_t keydata, void* param);

//RENDERS
void render_floor(t_scene *scene);
void render_ceiling(t_scene *scene);
void render_player(t_scene *scene);
void render_ray(t_scene *scene);

//AUX
int abs(int n); //NO ESTÁ EN MATH.H?
unsigned long createRGB(int r, int g, int b);
double calcular_angulo_grados(double x0, double y0, double x1, double y1);

//PLAYER
void initialize_player(t_scene *scene);
int populate_map(t_scene *scene, int map_width, int map_height, int map[][7]);