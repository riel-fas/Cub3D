/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riel-fas <riel-fas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 02:36:35 by riel-fas          #+#    #+#             */
/*   Updated: 2025/09/25 13:14:47 by riel-fas         ###   ########.fr       */
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
// # include "/Users/riel-fas/MLX42/include/MLX42/MLX42.h"
// # include "/Users/ssallami/MLX42/include/MLX42/MLX42.h"

# define BUFFER_SIZE 1024
# define TRUE 1
# define FALSE 0

/* Window settings */
# define TEXTURE_SIZE 64
# define WINDOW_WIDTH 1200
# define WINDOW_HEIGHT 750
# define WINDOW_TITLE "Cub3D"

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


typedef struct s_data
{
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
	
	/* Parsing flags */
	int			textures_parsed[4];	// individual texture flags
	int			colors_parsed[2];	// floor and ceiling flags
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


int	count_words_internal(char *str, char delimiter);


/* Function prototypes */

/* Main */
int		main(int argc, char **argv);
int		validate_args(int argc, char **argv);

/* Parsing */
int		parse_file(t_data *data, char *filename);
int		parse_textures_and_colors(t_data *data);
int		parse_map(t_data *data);
int		validate_map(t_data *data);

/* File content parsing */
int		iterate_through_lines(t_data *data);
int		process_lines_until_map(t_data *data);
int		is_empty_or_comment(char *line);
int		process_single_line(t_data *data, char *trimmed_line);
int		validate_parsing_completeness(t_data *data);
int		handle_line_processing_result(int result, char *trimmed_line);
int		process_single_line_with_cleanup(t_data *data, char *trimmed_line);
char	*get_trimmed_line(char **file_lines, int index);

/* Texture parsing */
int		get_texture_type(char *line);
int		validate_texture_extension(char *path);
int		parse_texture_line(t_data *data, char *line);

/* RGB/Color parsing */
int		parse_rgb_values(char *rgb_str, t_color *color);
int		parse_color_line(t_data *data, char *line);

/* Map parsing */
int		process_map_line_index(t_data *data, int file_index, int *map_index);
int		populate_map_data(t_data *data, int map_start);
int		is_config_line(char *trimmed_line);
int		should_skip_line(char *trimmed_line);
int		find_map_start(t_data *data);
int		count_map_lines(t_data *data, int start);
int		get_map_width(t_data *data, int start);
int		initialize_map_data(t_data *data, int *map_start);
int		allocate_map_memory(t_data *data);
int		add_line_to_map(t_data *data, char *trimmed_line, int map_index);

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

/* Flood fill validation */
void	flood_fill(char **map_copy, int x, int y, t_data *data);
int		validate_flood_fill_result(t_data *data, char **map_copy);
int		flood_fill_validation(t_data *data);

/* Player validation */
int		is_player_char(char c);
int		is_valid_char(char c);
int		count_and_set_player(t_data *data);
int		find_player_position(t_data *data);
int		validate_characters(t_data *data);

/* Border validation */
int		check_horizontal_borders(t_data *data);
int		check_vertical_borders(t_data *data);
int		check_map_borders(t_data *data);
int		is_space_connecting_to_border(t_data *data, int x, int y);
int		check_empty_spaces_near_borders(t_data *data);

/* Wall validation */
int		is_surrounded_by_walls(t_data *data, int x, int y);
int		validate_walls(t_data *data);

/* Advanced validation */
int		check_empty_lines_in_map(t_data *data);
int		validate_file_extension(char *filename);
int		validate_texture_files(t_data *data);
int		check_duplicate_configs(t_data *data);

/* Reference-style validation */
int		validate_map_boundaries(t_data *data);
int		check_directions_ver(t_data *data, int x, int y);
int		check_directions_hor(t_data *data, int x, int y);
int		check_line(t_data *data, int y);

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
char	*ft_strncpy(char *dest, const char *src, int n);

/* Error handling */
void	error_exit(char *message);
void	free_data(t_data *data);
void	free_split(char **split);

/* Additional map helper functions */
char	*pad_map_line(char *line, int target_width);
char	*process_map_line(char *file_line);

#endif
