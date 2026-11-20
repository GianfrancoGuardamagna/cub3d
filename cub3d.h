#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42/include/MLX42/MLX42.h"
# include <math.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include "./libft/libft.h"

# ifndef WIDTH
#  define WIDTH 1800
# endif
# ifndef HEIGHT
#  define HEIGHT 1200
# endif
/* # ifndef MAP_WIDTH
#  define MAP_WIDTH 7
# endif
# ifndef MAP_HEIGHT
#  define MAP_HEIGHT 5
# endif */
# ifndef PLAYER_FOV
#  define PLAYER_FOV 60
# endif
# ifndef PLAYER_RADIUS
#  define PLAYER_RADIUS 15
# endif
# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif
# define CELL_SIZE 128
# define ROT_SPEED 0.05235987756
# define MOUSE_SENS 0.001
# define MINI_MARGIN 20
# define MINI_PLAYER_R 4
# define MINI_WALL 0x4D2FA1F5
# define MINI_FLOOR 0xC46535F5
# define MINI_PLAYER 0x5F19C093

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

/* typedef struct s_img
{
	void	*img_ptr;
	char	*pixels_ptr;
	int		bpp;
	int		endian;
	int		line_len;
	int		width;
	int		height;
}	t_img; */

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
	mlx_texture_t	*wall_n;
	mlx_texture_t	*wall_e;
	mlx_texture_t	*wall_s;
	mlx_texture_t	*wall_w;
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
	int				camera;
	double			last_mouse_x;
}	t_scene;

/* render, minimap, dda, collisions, movement, textures */

/* Casts one ray per window column and draws the whole 3D view. */
void			analize_fov(t_scene *scene);
/* Draws the minimap and the player marker in the top-left corner. */
void			paint_mapcell(t_scene *scene);
/* Casts one ray at the given angle offset; returns the distance to the wall. */
float			dda(t_scene *scene, float fov_offset);
/* Returns 1 if the map cell (y, x) is a wall or lies outside the map. */
int				is_wall_cell(t_scene *scene, int y, int x);
/* Returns 1 if the player's hitbox at (x, y) overlaps a wall. */
int				check_walls_around(t_scene *scene, int x, int y);
/* Moves the player forward (view direction) unless a wall blocks the way. */
void			moving_north(t_scene *scene, float move_x, float move_y);
/* Moves the player backward unless a wall blocks the way. */
void			moving_south(t_scene *scene, float move_x, float move_y);
/* Strafes the player to the right unless a wall blocks the way. */
void			moving_east(t_scene *scene, float right_x, float right_y);
/* Strafes the player to the left unless a wall blocks the way. */
void			moving_west(t_scene *scene, float right_x, float right_y);
/* Returns the RGBA color of the pixel (x, y) of a texture. */
uint32_t		get_pixel(mlx_texture_t *texture, int x, int y);
/* Returns the wall texture (N, S, E or W) matching the side hit by the ray. */
mlx_texture_t	*select_texture(t_scene *scene);

/* init and events */

/* Loads the four wall textures, then creates the window and the image. */
void			init_scene(t_scene *scene);
/* Sets the player position, direction and speed from the spawn cell. */
void			init_player(t_scene *scene);
/* Registers the loop, mouse and key hooks of the game. */
void			init_events(t_scene *scene);
/* Rotates the player's direction vector by an angle given in radians. */
void			rotate_player(t_scene *scene, double angle);
/* Rotates the view with the left and right arrow keys. */
void			handle_camera_keys(t_scene *scene);
/* Rotates the view following the mouse movement (only when enabled). */
void			handle_camera_mouse(double xpos, double ypos, void *param);
/* Handles single key presses: C toggles the mouse look, ESC closes the game. */
void			handle_key_event(mlx_key_data_t keydata, void *param);

/* errors and cleanup */

/* Prints "Error" and a message, frees everything and exits with the status. */
void			error_call(t_scene *scene, int status, char *msg);
/* Reads the rest of the file so get_next_line frees its internal buffer. */
void			drain_gnl(int fd);
/* Frees the textures, the window, the parsed data and the scene itself. */
void			clean_exit(t_scene *scene);

/* parsing - file and header lines */

/* Checks that the file name ends with ".cub". */
int				check_extension(char *str);
/* Opens the file and reads it line by line: header first, then the map. */
int				read_fd(char *file, t_scene *scene);
/* Checks that all four textures and both colors have been found. */
int				check_info(t_scene *scene);
/* Stores the line's value if it starts with a texture or color identifier. */
void			check_line_type(t_scene *scene, char *line);
/* Returns a trimmed copy of the value that follows the identifier. */
char			*extract_data(char *line);
/* Checks that the header is complete, then starts reading the map. */
int				handle_map_start(t_scene *scene, char *line, int fd);
/* Reports the error that applies when the file ends without a map. */
int				check_eof_errors(t_scene *scene);

/* parsing - colors */

/* Checks a color string: exactly two commas, only digits, commas and spaces. */
int				valid_rgb_format(char *str);
/* Converts an "R,G,B" string into one RGBA value; returns 1 on error. */
int				extract_color_numbers(char *line, uint32_t *dest_color);
/* Converts the floor and ceiling colors; returns 1 if either is invalid. */
int				error_colors(t_scene *scene);
/* Returns how many commas a string contains. */
int				count_commas(char *line);
/* Frees a NULL-terminated array of strings and the array itself. */
void			ft_free_matrix(char **array);

/* parsing - map */

/* Stores the map rows read from the file in scene->map.grid. */
int				parse_map(t_scene *scene, char *first_line, int fd);
/* Returns a new grid with one more row appended and frees the old array. */
char			**expand_grid(char **old_grid, char *new_line);
/* Returns the number of rows of a NULL-terminated grid. */
int				get_grid_rows(char **grid);
/* Returns the length of the longest row, not counting the newline. */
int				get_grid_cols(char **grid);

/* validate map */

/* Returns 1 if the cell is a space, a newline or lies outside the map. */
int				is_open(t_scene *scene, int y, int x);
/* Returns 1 if any of the four neighbors of a cell is open. */
int				touches_void(t_scene *scene, int y, int x);
/* Checks that no walkable cell touches an open cell (the map is closed). */
int				check_close_map(t_scene *scene);
/* Checks that a row only has valid characters and counts the players in it. */
int				check_row(char *row, int *players);
/* Checks every character of the map and that there is exactly one player. */
int				check_chars_and_player(t_scene *scene);
/* Runs all the map checks: characters, single player and closed map. */
int				validate_map(t_scene *scene);

#endif
