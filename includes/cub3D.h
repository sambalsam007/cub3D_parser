/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-rudd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:03:42 by yde-rudd          #+#    #+#             */
/*   Updated: 2025/07/15 14:39:00 by yde-rudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <time.h>
# include <fcntl.h>
# include <unistd.h>
# include "../sources/libft/libft.h"
# include "../sources/libft/sources/get_next_line/get_next_line.h"
# include "../sources/minilibx-linux/mlx.h"

// *** GAME INFORMATION ***
# define WIN_HEIGHT 512
# define WIN_WIDTH 1024
# define SIZE_P_MINIMAP 20
# define MOVE_SPEED 0.009
# define MOUSE_SENSITIVITY 0.0001
# define MOUSE_RESET_MARGIN 20
# define MOUSE_RESET_THROTTLE 6 // mouse resets per second
# define MIN_FRAME_TIME 0.01667 // 60 FPS
# define FILE_LINE_CAP 32
# define IMAGE_SIZE 64
# define TAB_WIDTH 4

// *** KEYCODES ***
# define ESC_KEY 65307
# define LEFT_ARROW 65361
# define RIGHT_ARROW 65363
# define DOWN_ARROW 65364
# define UP_ARROW 65362
# define W_KEY 119
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100
# define Q_KEY 113

// *** COLOR CODES ***
# define BOLD_MAGENTA "\033[35m"
# define BOLD_RED "\033[31m"
# define BOLD_BLUE "\033[1;94m"
# define BOLD_GREEN "\033[32m"
# define RESET "\033[0m"

// *** STRUCTS ***
typedef struct s_point
{
	double	x;
	double	y;
}	t_point;

typedef struct s_player
{
	t_point		pos;
	double		angle;
	t_point		prev_pos;
	double		prev_angle;
}	t_player;

typedef struct s_map
{
	char		**data;
	int			width;
	int			height;
	// config elements
	char		*no_texture;
	char		*so_texture;
	char		*ea_texture;
	char		*we_texture;
	int			floor_color;
	int			ceiling_color;

}	t_map;

typedef struct s_image
{
	void	*no_img;
	void	*so_img;
	void	*we_img;
	void	*ea_img;
}	t_image;

typedef struct s_game
{
	t_player	player;
	t_map		map;
	t_image		*images;
	void		*mlx;
	void		*window;
}	t_game;

// *** INITIALIZING & PARSING***
bool	init_game(t_game *game);
bool	parse_cub_file(const char *filename, t_map *map);
bool	validate_map(t_map *map);
bool	is_map_enclosed(t_map *map);
bool	check_single_player(t_map *map);
bool	load_in_images(t_game *game);
void	init_directions(int *dx, int *dy);

// *** FREEING ***
void	free_game(t_game *game);
void	free_mlx(t_game *game);

// *** UTILS ***
void	print_error(char *str);
void	print_map_data(t_map *data);
char	*skip_leading_whitespaces(const char *line);
bool	is_empty_line(const char *line);

#endif
