/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-rudd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 11:02:11 by yde-rudd          #+#    #+#             */
/*   Updated: 2025/07/15 14:36:47 by yde-rudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

bool	check_single_player(t_map *map)
{
	int	i;
	int	j;
	int	player_count;

	i = 0;
	j = 0;
	player_count = 0;
	while (i < map->height)
	{
		j = 0;
		while (map->data[i][j])
		{
			if (map->data[i][j] == 'N' || map->data[i][j] == 'S'
				|| map->data[i][j] == 'E' || map->data[i][j] == 'W')
				player_count++;
			j++;
		}
		i++;
	}
	if (player_count != 1)
		return (print_error("map must contain exactly one player"), false);
	return (true);
}

static bool	is_neighbor_valid(char **map, int nx, int ny, int height)
{
	if (nx < 0 || nx >= height || ny < 0
		|| ny >= (int)ft_strlen(map[nx]))
		return (false);
	if (map[nx][ny] == ' ')
		return (false);
	return (true);
}

static bool	check_neighbors(char **map, int row, int col, int height)
{
	int		dx[4];
	int		dy[4];
	int		d;
	int		nx;
	int		ny;

	init_directions(dx, dy);
	d = 0;
	while (d < 4)
	{
		nx = row + dx[d];
		ny = col + dy[d];
		if (!is_neighbor_valid(map, nx, ny, height))
			return (false);
		d++;
	}
	return (true);
}

static bool	is_valid_surrounding(char **map, int row, int col, int height)
{
	char	c;

	c = map[row][col];
	if (c != '0' && c != 'N' && c != 'S' && c != 'E' && c != 'W')
		return (true);
	return (check_neighbors(map, row, col, height));
}

bool	is_map_enclosed(t_map *map)
{
	int	height;
	int	row;
	int	col;
	int	width;

	height = map->height;
	row = 0;
	col = 0;
	width = 0;
	while (row < height)
	{
		width = ft_strlen(map->data[row]);
		col = 0;
		while (col < width)
		{
			if (!is_valid_surrounding(map->data, row, col, height))
				return (printf(BOLD_RED"Error:\nMap error at row %d col %d\n"
						RESET, row, col), false);
			col++;
		}
		row++;
	}
	return (true);
}

bool	validate_map(t_map *map)
{
	if (map->height <= 2 || map->width <= 2)
		return (print_error("invalid map height or width"), false);
	if (map->floor_color == -1 || map->ceiling_color == -1)
		return (false);
	if (!check_single_player(map))
		return (false);
	if (!is_map_enclosed(map))
		return (false);
	return (true);
}
