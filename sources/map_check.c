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

static bool is_valid_surrounding(char **map, int row, int col, int height)
{
	char	c;

	c = map[row][col];
    if (c != '0' && c != 'N' && c != 'S' && c != 'E' && c != 'W')
        return (true);

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    for (int d = 0; d < 4; d++) {
        int nx = row + dx[d];
        int ny = col + dy[d];

        if (nx < 0 || nx >= height)
            return (false);

        if (ny < 0 || ny >= (int)ft_strlen(map[nx]))
            return (false);

        char neighbor = map[nx][ny];
        if (neighbor == ' ')
            return (false);
    }

    return (true);
}

bool is_map_enclosed(t_map *map)
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
		col =  0;
		while (col < width)
		{
			if (!is_valid_surrounding(map->data, row, col, height))
			{
				printf(BOLD_RED"Error:\nMap error at row %d col %d\n"RESET, row, col);
				return (false);
			}
			col++;
		}
		row++;
	}
	return (true);
}

