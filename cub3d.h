#include "MLX42/include/MLX42/MLX42.h"
#include <math.h>
#include <X11/X.h>
#include <X11/keysym.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "./libft/libft.h"

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
	uint32_t	color;
	char		*f;
}	t_floor;

typedef struct s_ceiling
{
	uint32_t	color;
	char		*c;
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
	mlx_texture_t	*wall_N;
	mlx_texture_t	*wall_E;
	mlx_texture_t	*wall_S;
	mlx_texture_t	*wall_W;
	char			*north;
	char			*east;
	char			*south;
	char			*west;
}	t_texture;

typedef struct s_map
{
	char	**grid;
	int		rows;
	int		cols;
}	t_map;

typedef struct s_scene
{
	void			*mlx_connection;
	mlx_image_t		*img;
	t_ceiling		ceiling;
	t_floor			floor;
	t_player		player;
	t_ray			ray;
	t_map			map;
	t_texture		texture;
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

// parsing - check_file
int			check_extension(char *str);
int			read_fd(char *file, t_scene *scene); // Abro archivo y llamo al gnl para la lectura de este
//int			handle_map_start(t_scene *scene, char *line, int fd);
int			check_info(t_scene *scene); //Compruebo si estan los punteros de las texturas, cielo y suelo vacios
void		check_line_type(t_scene *scene, char *line); // Comparamos si line = a los puntos cardinales, el cielo o el suelo. Si lo es entramos en las funciones correspondientes
char		*extract_data(char *line);
int			valid_rgb_format(char *str);
int			extract_color_numbers(char *line, uint32_t *dest_color);

// parsing map
int			parse_map(t_scene *scene, char *first_line, int fd);
char		**expand_grid(char **old_grid, char *new_line);
int			get_grid_rows(char **grid);

//utils
int			count_commas(char *line);
void		ft_free_matrix(char **array);
void		clean_exit(t_scene *scene);
int			error_colors(t_scene *scene);




