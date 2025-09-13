/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: your_login <your_login@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 12:00:00 by your_login       #+#    #+#             */
/*   Updated: 2024/01/01 12:00:00 by your_login      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <math.h>
/* ===== ENGINE INCLUDES (COMMENTED OUT FOR PARSING PHASE) =====
 * TODO: Uncomment when peer starts working on the engine
 */
/* # include <MLX42.h> */
/* ===== END ENGINE INCLUDES ===== */

# define BUFFER_SIZE 1024
# define TRUE 1
# define FALSE 0

/* Window settings */
# define WINDOW_WIDTH 1024
# define WINDOW_HEIGHT 768
# define WINDOW_TITLE "Cub3D - 3D Raycasting Engine"

/* Game settings */
# define FOV 1.047198		// 60 degrees in radians (PI/3)
# define MOVE_SPEED 0.1
# define ROTATE_SPEED 0.03
# define TEXTURE_SIZE 64

/* Math constants */
# define PI 3.14159265359
# define TWO_PI 6.28318530718

/* Error messages */
# define ERR_ARGS "Error\nUsage: ./cub3D <map.cub>\n"
# define ERR_FILE "Error\nCannot open file\n"
# define ERR_EXTENSION "Error\nFile must have .cub extension\n"
# define ERR_TEXTURE "Error\nInvalid texture path\n"
# define ERR_COLOR "Error\nInvalid color format\n"
# define ERR_MAP "Error\nInvalid map\n"
# define ERR_MALLOC "Error\nMemory allocation failed\n"
# define ERR_DUPLICATE "Error\nDuplicate configuration\n"
# define ERR_MISSING "Error\nMissing configuration\n"
# define ERR_INVALID_CHAR "Error\nInvalid character in map\n"
# define ERR_NO_PLAYER "Error\nNo player found in map\n"
# define ERR_MULTI_PLAYER "Error\nMultiple players found in map\n"
# define ERR_MAP_NOT_CLOSED "Error\nMap is not closed/surrounded by walls\n"
# define ERR_EMPTY_LINE "Error\nEmpty line in map\n"
# define ERR_INVALID_RGB "Error\nRGB values must be between 0-255\n"

/* Map characters */
# define WALL '1'
# define EMPTY '0'
# define NORTH 'N'
# define SOUTH 'S'
# define EAST 'E'
# define WEST 'W'

/* Texture identifiers */
typedef enum e_texture_type
{
	NO = 0,	// North texture
	SO = 1,	// South texture
	WE = 2,	// West texture
	EA = 3,	// East texture
	F = 4,	// Floor color
	C = 5	// Ceiling color
}	t_texture_type;

/* Color structure */
typedef struct s_color
{
	int	r;
	int	g;
	int	b;
	int	hex;		// Hex representation for MLX
}	t_color;

/* Vector structure for raycasting */
typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

/* Ray structure */
typedef struct s_ray
{
	t_vector	pos;		// Ray position
	t_vector	dir;		// Ray direction
	t_vector	delta_dist;	// Distance between x/y intersections
	t_vector	side_dist;	// Distance to next x/y intersection
	t_vector	step;		// Step direction (-1 or 1)
	int			map_x;		// Current map position
	int			map_y;
	int			hit;		// Wall hit flag
	int			side;		// Which side was hit (0=x, 1=y)
	double		wall_dist;	// Distance to wall
	int			line_height;// Height of wall line to draw
	int			draw_start;	// Start pixel of wall
	int			draw_end;	// End pixel of wall
	int			tex_num;	// Texture number (0-3)
	double		wall_x;		// Exact wall hit position
	int			tex_x;		// Texture x coordinate
}	t_ray;

/* ===== ENGINE STRUCTURES (COMMENTED OUT FOR PARSING PHASE) =====
 * TODO: Uncomment when peer starts working on the engine
 */
/* Texture structure */
/* typedef struct s_texture
{
	mlx_texture_t	*mlx_texture;
	int				width;
	int				height;
	uint32_t		**pixels;	// 2D array of pixel data
}	t_texture; */
/* ===== END ENGINE STRUCTURES ===== */

/* Game data structure */
typedef struct s_data
{
	/* ===== ENGINE FIELDS (COMMENTED OUT FOR PARSING PHASE) =====
	 * TODO: Uncomment when peer starts working on the engine
	 */
	/* MLX */
	/* mlx_t		*mlx; */
	/* mlx_image_t	*image; */
	
	/* Textures */
	char		*texture_paths[4];	// NO, SO, WE, EA
	/* t_texture	textures[4]; */		// Loaded texture data
	t_color		floor_color;
	t_color		ceiling_color;
	
	/* Map */
	char		**map;
	int			map_width;
	int			map_height;
	
	/* Player */
	double		player_x;
	double		player_y;
	char		player_dir;		// N, S, E, W
	double		player_angle;	// Angle in radians
	/* t_vector	player_pos; */		// Player position vector
	/* t_vector	player_dir_vec; */	// Player direction vector
	/* t_vector	camera_plane; */	// Camera plane vector
	
	/* Game state */
	/* int			game_running; */
	
	/* Input state for smooth movement */
	/* struct {
		int		w_pressed;
		int		a_pressed;
		int		s_pressed;
		int		d_pressed;
		int		left_pressed;
		int		right_pressed;
	}			keys; */
	/* ===== END ENGINE FIELDS ===== */
	
	/* Parsing flags */
	int			textures_parsed[4];	// Individual texture flags
	int			colors_parsed[2];	// Floor and ceiling flags
	int			map_started;
	int			parsing_complete;
	
	/* File data */
	char		**file_lines;
	int			line_count;
	char		*filename;
	
	/* Validation data */
	int			empty_lines_in_map;
	int			**visited;		// For flood fill algorithm
}	t_data;

/* Function prototypes */

/* Main */
int		main(int argc, char **argv);
int		validate_args(int argc, char **argv);

/* ===== ENGINE FUNCTION PROTOTYPES (COMMENTED OUT FOR PARSING PHASE) =====
 * TODO: Uncomment when peer starts working on the engine
 
// Game initialization
// int		init_game(t_data *data);
// int		init_mlx(t_data *data);
// int		init_player(t_data *data);
// void	setup_player_vectors(t_data *data);

// Texture loading
// int		load_textures(t_data *data);
// int		load_single_texture(t_data *data, int index);
// void	convert_texture_pixels(t_texture *texture);
// uint32_t get_pixel_color(t_texture *texture, int x, int y);

// Game loop
// void	game_loop(void *param);
// void	update_game(t_data *data);
// void	render_frame(t_data *data);

// Raycasting
// void	cast_rays(t_data *data);
// void	cast_single_ray(t_data *data, int x);
// void	init_ray(t_data *data, t_ray *ray, int x);
// void	calculate_step_and_side_dist(t_data *data, t_ray *ray);
// void	perform_dda(t_data *data, t_ray *ray);
// void	calculate_wall_distance(t_ray *ray);
// void	calculate_draw_bounds(t_ray *ray);

// Rendering
// void	draw_vertical_line(t_data *data, int x, t_ray *ray);
// void	draw_textured_wall(t_data *data, int x, t_ray *ray);
// void	draw_floor_and_ceiling(t_data *data, int x, t_ray *ray);
// uint32_t get_texture_pixel(t_data *data, t_ray *ray, int y);

// Input handling
// void	handle_input(mlx_key_data_t keydata, void *param);
// void	handle_mouse(double xpos, double ypos, void *param);
// void	process_movement(t_data *data);
// void	move_player(t_data *data, double move_x, double move_y);
// void	rotate_player(t_data *data, double angle);

// Math utilities
// double	normalize_angle(double angle);
// double	distance(double x1, double y1, double x2, double y2);
// int		rgb_to_hex(int r, int g, int b);

// Cleanup
// void	cleanup_game(t_data *data);
// void	cleanup_textures(t_data *data);
 ===== END ENGINE FUNCTION PROTOTYPES ===== */

/* Parsing */
int		parse_file(t_data *data, char *filename);
int		parse_textures_and_colors(t_data *data);
int		parse_map(t_data *data);
int		validate_map(t_data *data);

/* Parsing utils */
int		is_texture_line(char *line);
int		is_color_line(char *line);
int		is_map_line(char *line);
int		parse_texture_path(t_data *data, char *line);
int		parse_color(t_data *data, char *line);
int		skip_whitespace(char *line, int *index);
int		get_texture_index(char *line);

/* Map validation */
int		is_valid_map_char(char c);
int		check_walls(t_data *data);
int		find_player(t_data *data);
int		flood_fill_check(t_data *data);
int		validate_map_format(t_data *data);

/* Advanced validation */
int		check_empty_lines_in_map(t_data *data);
int		validate_file_extension(char *filename);
int		validate_texture_files(t_data *data);
int		check_duplicate_configs(t_data *data);

/* Utils */
int		ft_strlen(char *str);
char	*ft_strdup(char *str);
char	**ft_split(char *str, char delimiter);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strtrim(char *str);
int		ft_isdigit(char c);
int		ft_atoi(char *str);
int		ft_isspace(char c);
char	*ft_strchr(char *str, char c);
int		count_words(char *str, char delimiter);

/* Error handling */
void	error_exit(char *message);
void	free_data(t_data *data);
void	free_split(char **split);

#endif
