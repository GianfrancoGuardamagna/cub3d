#include "MLX42/include/MLX42/MLX42.h"
#include <math.h>
#include <X11/X.h>
#include <X11/keysym.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#ifndef WIDTH
#define WIDTH 900
#endif
#ifndef HEIGHT
#define HEIGHT 600
#endif
#ifndef MAP_WIDTH
#define MAP_WIDTH 7
#endif
#ifndef MAP_HEIGHT
#define MAP_HEIGHT 5
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
	mlx_image_t *img;
	t_ceiling ceiling;
	t_floor floor;
	t_player player;
	t_ray ray;
	int **map;
	t_texture texture;
}	t_scene;

// Main
void		analize_fov(t_scene *scene);
void		paint_mapcell(t_scene *scene);

// ./DDA
// dda.c
float		dda(t_scene *scene, float fov_offset);

// ./utils
// error.c
void		error_call(t_scene *scene, int status, char *msg);

// init_scene.c
void		init_scene(t_scene *scene);

// init_player.c
void		init_player(t_scene *scene);

// init_events.c
void		init_events(t_scene *scene);
void		close_handler(void* param);

// moves.c
void		moving_north(t_scene *scene, float move_x, float move_y);
void		moving_south(t_scene *scene, float move_x, float move_y);
void		moving_east(t_scene *scene, float right_x, float right_y);
void		moving_west(t_scene *scene, float right_x, float right_y);

// collision.c
int			check_walls_around(t_scene *scene, int x, int y);

// textures.c
uint32_t	get_pixel(mlx_texture_t *texture);
void		select_texture(t_scene *scene, mlx_texture_t *texture);