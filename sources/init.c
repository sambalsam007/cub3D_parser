/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-rudd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:40:24 by yde-rudd          #+#    #+#             */
/*   Updated: 2025/03/08 01:57:29 by yde-rudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static void	init_map(t_game *game)
{
	game->map.width = 0;
	game->map.height = 0;
	game->map.data = NULL;
	game->map.no_texture = '\0';
	game->map.ea_texture = '\0';
	game->map.so_texture = '\0';
	game->map.we_texture = '\0';
	game->map.floor_color = -1; // will point out error
	game->map.ceiling_color = -1;
}
/*
static t_map	init_map(char *filename)
{
	int		fd;
	char	*line;
	t_map	map;

	map.data = NULL;
	map.height = 0;
	map.width = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (print_error("Error opening file"), map);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
//		parse_line(game, line); // TODO
		free(line);
	}
	close(fd);
	return (map);
}*/

void	init_game(t_game *game)
{
	printf(BOLD_BLUE"Initializing game\n"RESET);

	init_map(game);
	return ;
}
