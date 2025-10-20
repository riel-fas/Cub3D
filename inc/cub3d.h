/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 02:36:35 by riel-fas          #+#    #+#             */
/*   Updated: 2025/10/20 18:27:48 by riel-fas         ###   ########.fr       */
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
// # include "/Users/ref/MLX42/include/MLX42/MLX42.h"
# include "/Users/riel-fas/MLX42/include/MLX42/MLX42.h"

# define BUFFER_SIZE 1024
# define TRUE 1
# define FALSE 0

/* Window settings */
# define TEXTURE_SIZE 64
# define WINDOW_WIDTH 1200
# define WINDOW_HEIGHT 750
# define WINDOW_TITLE "Cub3D"

/* Game settings */
# define FOV 1.047198
# define MOVE_SPEED 0.1
# define ROTATE_SPEED 0.15
# define TEXTURE_SIZE 64

/* Animation/HUD settings */
# define ZOMBIE_HUD_SIZE 200     // Size of the zombie animation HUD
# define ZOMBIE_HUD_X_OFFSET 20  // Distance from screen edge
# define ZOMBIE_HUD_Y_OFFSET 20  // Distance from screen edge
# define ZOMBIE_FRAME_RATE 0.05   // Time between frames (seconds)

/* First-person hands settings */
# define FP_HANDS_WIDTH_SCALE 0.8   // 80% of screen width (was 0.6)
# define FP_HANDS_HEIGHT_SCALE 0.7  // 70% of screen height (was 0.5)
# define FP_HANDS_Y_OFFSET 50       // Pixels up from bottom

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
# define WALL 49
# define EMPTY 48
# define NORTH 78
# define SOUTH 83
# define EAST 69
# define WEST 87
# define DOOR 68

/* Texture identifiers */
typedef enum e_texture_type
{
	NO = 0,
	SO = 1,
	WE = 2,
	EA = 3,
	F = 4,
	C = 5
}	t_texture_type;

/* Color structure */
typedef struct s_color
{
	int	r;
	int	g;
	int	b;
	int	hex;
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
	t_vector	pos;
	t_vector	dir;
	t_vector	delta_dist;	
	t_vector	side_dist;
	t_vector	step;
	int			map_x;
	int			map_y;
	int			hit;
	int			side;
	double		wall_dist;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			tex_num;
	double		wall_x;
	int			tex_x;
	int			is_door;
}	t_ray;

/* Texture structure */
typedef struct s_texture
{
	mlx_texture_t	*mlx_texture;
	int				width;
	int				height;
	uint32_t		**pixels;
}	t_texture;

/* Animation frame structure */
typedef struct s_anim_frame
{
	t_texture		texture;
	int				frame_number;
}	t_anim_frame;

/* Animation structure */
typedef struct s_animation
{
	t_anim_frame	*frames;
	int				frame_count;
	int				current_frame;
	double			frame_duration;
	double			last_update;
	int				is_playing;
	int				loop;
	char			*base_path;
}	t_animation;

/* Helper structures for rendering */
typedef struct s_pixel_coords
{
	int	tex_x;
	int	tex_y;
	int	screen_x;
	int	screen_y;
}	t_pixel_coords;

typedef struct s_hands_render_info
{
	int	x;
	int	y;
	int	hands_x;
	int	hands_y;
	int	hands_width;
	int	hands_height;
}	t_hands_render_info;

/* Key state structure */
typedef struct s_keys
{
	int	w_pressed;
	int	a_pressed;
	int	s_pressed;
	int	d_pressed;
	int	left_pressed;
	int	right_pressed;
}	t_keys;

typedef struct s_data
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	char		*texture_paths[4];
	t_texture	textures[4];
	t_texture	door_texture;
	t_color		floor_color;
	t_color		ceiling_color;
	char		**map;
	int			map_width;
	int			map_height;
	double		player_x;
	double		player_y;
	char		player_dir;
	double		player_angle;
	t_vector	player_pos;
	t_vector	player_dir_vec;
	t_vector	camera_plane;
	int			game_running;
	t_keys		keys;
	int			textures_parsed[4];
	int			colors_parsed[2];
	int			map_started;
	int			parsing_complete;
	char		**file_lines;
	int			line_count;
	char		*filename;
	int			empty_lines_in_map;
	int			**visited;
	t_animation	zombie_anim;
	double		current_time;
	char		**door_states;
}	t_data;

/* Function prototypes */
/* Main */
int			main(int argc, char **argv);
int			validate_args(int argc, char **argv);
void		print_parsing_summary(t_data *data);
void		print_texture_status(t_data *data);
void		print_color_status(t_data *data);
void		init_textures_and_colors(t_data *data);
void		init_map_and_player(t_data *data);
void		init_data(t_data *data);
int			check_file_extension(char *filename);

/* Parsing */
int			parse_file(t_data *data, char *filename);
int			parse_textures_and_colors(t_data *data);
int			parse_map(t_data *data);
int			validate_map(t_data *data);
int			count_words_internal(char *str, char delimiter);

/* File content parsing */
int			iterate_through_lines(t_data *data);
int			process_lines_until_map(t_data *data);
int			is_empty_or_comment(char *line);
int			process_single_line(t_data *data, char *trimmed_line);
int			validate_parsing_completeness(t_data *data);
int			handle_line_processing_result(int result, char *trimmed_line);
int			process_single_line_with_cleanup(t_data *data, char *trimmed_line);
char		*get_trimmed_line(char **file_lines, int index);

/* Texture parsing */
int			get_texture_type(char *line);
int			validate_texture_extension(char *path);
int			parse_texture_line(t_data *data, char *line);

/* RGB/Color parsing */
int			parse_rgb_values(char *rgb_str, t_color *color);
int			parse_color_line(t_data *data, char *line);

/* Map parsing */
int			process_map_line_index(t_data *data,
				int file_index, int *map_index);
int			populate_map_data(t_data *data, int map_start);
int			is_config_line(char *trimmed_line);
int			should_skip_line(char *trimmed_line);
int			find_map_start(t_data *data);
int			count_map_lines(t_data *data, int start);
int			get_map_width(t_data *data, int start);
int			initialize_map_data(t_data *data, int *map_start);
int			allocate_map_memory(t_data *data);
int			add_line_to_map(t_data *data, char *trimmed_line, int map_index);

/* Parsing utils */
int			is_texture_line(char *line);
int			is_color_line(char *line);
int			is_map_line(char *line);
int			parse_texture_path(t_data *data, char *line);
int			parse_color(t_data *data, char *line);
int			skip_whitespace(char *line, int *index);
int			get_texture_index(char *line);

/* Map validation */
int			is_valid_map_char(char c);
int			check_walls(t_data *data);
int			find_player(t_data *data);
int			flood_fill_check(t_data *data);
int			validate_map_format(t_data *data);

/* Flood fill validation */
void		flood_fill(char **map_copy, int x, int y, t_data *data);
int			validate_flood_fill_result(t_data *data, char **map_copy);
int			flood_fill_validation(t_data *data);

/* Player validation */
int			is_player_char(char c);
int			is_valid_char(char c);
int			count_and_set_player(t_data *data);
int			find_player_position(t_data *data);
int			validate_characters(t_data *data);

/* Border validation */
int			check_horizontal_borders(t_data *data);
int			check_vertical_borders(t_data *data);
int			check_map_borders(t_data *data);
int			is_space_connecting_to_border(t_data *data, int x, int y);
int			check_empty_spaces_near_borders(t_data *data);

/* Wall validation */
int			is_surrounded_by_walls(t_data *data, int x, int y);
int			validate_walls(t_data *data);

/* Advanced validation */
int			check_empty_lines_in_map(t_data *data);
int			validate_file_extension(char *filename);
int			validate_texture_files(t_data *data);
int			check_duplicate_configs(t_data *data);

/* Reference-style validation */
int			validate_map_boundaries(t_data *data);
int			check_directions_ver(t_data *data, int x, int y);
int			check_directions_hor(t_data *data, int x, int y);
int			check_line(t_data *data, int y);

/* Utils */
int			ft_strlen(char *str);
char		*ft_strdup(char *str);
char		**ft_split(char *str, char delimiter);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strtrim(char *str);
int			ft_isdigit(char c);
int			ft_atoi(char *str);
int			ft_isspace(char c);
char		*ft_strchr(char *str, char c);
int			count_words(char *str, char delimiter);
char		*ft_strncpy(char *dest, const char *src, int n);

/* Error handling */
void		error_exit(char *message);
void		free_data(t_data *data);
void		free_split(char **split);

/* Additional map helper functions */
char		*pad_map_line(char *line, int target_width);
char		*process_map_line(char *file_line);

/* Engine functions */
int			init_game(t_data *data);
int			init_mlx(t_data *data);
int			init_player(t_data *data);
void		setup_player_vectors(t_data *data);
void		setup_player_position(t_data *data);
void		setup_direction_north(t_data *data);
void		setup_direction_south(t_data *data);
void		setup_direction_east(t_data *data);
void		setup_direction_west(t_data *data);
void		setup_player_direction_vectors(t_data *data);
void		finalize_player_setup(t_data *data);
int			load_textures(t_data *data);
void		cleanup_textures(t_data *data);
uint32_t	get_pixel_color(t_texture *texture, int x, int y);
uint32_t	rgb_to_hex(int r, int g, int b);
void		process_forward_backward(t_data *data);
void		process_strafe(t_data *data);
void		handle_movement_keys(mlx_key_data_t keydata, t_data *data);
void		handle_rotation_keys(mlx_key_data_t keydata, t_data *data);
void		handle_w_key(mlx_key_data_t keydata, t_data *data);
void		handle_a_key(mlx_key_data_t keydata, t_data *data);
void		handle_s_key(mlx_key_data_t keydata, t_data *data);
void		handle_d_key(mlx_key_data_t keydata, t_data *data);
void		handle_f_key(mlx_key_data_t keydata, t_data *data);
void		handle_rotation_keys(mlx_key_data_t keydata, t_data *data);
void		calculate_line_height_and_bounds(t_ray *ray);
void		calculate_line_height_and_bounds(t_ray *ray);
void		calculate_texture_coordinates(t_ray *ray);
void		determine_texture_number(t_ray *ray);
int			load_single_texture(t_data *data, int index);
void		convert_texture_pixels(t_texture *texture);
void		init_fallback_texture_properties(t_texture *texture);
int			allocate_fallback_pixel_arrays(t_texture *texture);
void		generate_checkerboard_row(t_texture *texture, 
				int y, uint32_t color);
int			create_fallback_texture(t_texture *texture, uint32_t color);
int			handle_fallback_texture(t_data *data, int index);

/* Raycasting */
void		cast_rays(t_data *data);
void		init_ray(t_data *data, t_ray *ray, int x);
void		calculate_step_and_side_dist(t_data *data, t_ray *ray);
void		perform_dda(t_data *data, t_ray *ray);
void		calculate_wall_distance(t_ray *ray);
void		calculate_draw_bounds(t_ray *ray);
void		cast_single_ray(t_data *data, int x);

/* Rendering */
void		render_frame(t_data *data);
void		draw_vertical_line(t_data *data, int x, t_ray *ray);
void		draw_textured_wall(t_data *data, int x, t_ray *ray);
void		draw_floor_and_ceiling(t_data *data, int x, t_ray *ray);
uint32_t	get_texture_pixel(t_data *data, t_ray *ray, int y);
void		render_zombie_hud(t_data *data);
void		render_first_person_zombie_hands(t_data *data);

/* Input handling */
void		handle_input(mlx_key_data_t keydata, void *param);
void		handle_mouse(double xpos, double ypos, void *param);
void		process_movement(t_data *data);
void		move_player(t_data *data, double move_x, double move_y);
void		move_player_x(t_data *data, double move_x);
void		move_player_y(t_data *data, double move_y);
void		rotate_player(t_data *data, double angle);

/* Game loop */
void		game_loop(void *param);
void		update_game(t_data *data);

/* Math utilities */
double		degrees_to_radians(double degrees);
double		normalize_angle(double angle);

/* Animation system */
int			init_animation(t_animation *anim, 
				char *base_path, double frame_duration);
int			load_animation_frames(t_animation *anim);
void		update_animation(t_animation *anim, double current_time);
void		play_animation(t_animation *anim);
void		pause_animation(t_animation *anim);
void		reset_animation(t_animation *anim);
t_texture	*get_current_frame(t_animation *anim);
void		cleanup_animation(t_animation *anim);
double		get_current_time(void);
int			load_all_frames(t_animation *anim);
void		cleanup_partial_frames(t_animation *anim, int loaded_count);
int			allocate_animation_frames(t_animation *anim);
void		cleanup_frame_texture(t_texture *texture);
int			load_single_frame(t_animation *anim, int frame_num);
int			setup_frame_pixels(t_texture *texture);
int			load_frame_texture(t_texture *texture, char *frame_path);
void		build_frame_path(char *frame_path, char *base_path, int frame_num);
void		add_frame_number(char *frame_path, int len, int frame_num);
void		add_frame_prefix(char *frame_path, int len);
void		copy_base_path(char *frame_path, char *base_path, int *len);

/* Door system */
void		init_door_states(t_data *data);
void		free_door_states(t_data *data);
void		toggle_door(t_data *data);
int			is_door_open(t_data *data, int x, int y);
int			load_door_texture(t_data *data);

#endif
