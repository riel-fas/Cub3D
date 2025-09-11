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
# include "MLX42/MLX42.h"

# define BUFFER_SIZE 1024
# define TRUE 1
# define FALSE 0

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
}	t_color;

/* Game data structure */
typedef struct s_data
{
	/* Textures */
	char		*texture_paths[4];	// NO, SO, WE, EA
	t_color		floor_color;
	t_color		ceiling_color;
	
	/* Map */
	char		**map;
	int			map_width;
	int			map_height;
	
	/* Player */
	float		player_x;
	float		player_y;
	char		player_dir;		// N, S, E, W
	float		player_angle;	// Angle in radians
	
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
