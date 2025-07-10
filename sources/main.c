/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-rudd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:47:17 by yde-rudd          #+#    #+#             */
/*   Updated: 2025/03/08 01:43:05 by yde-rudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static bool	is_cub_file(const char *filename)
{
	const char	*dot;

	dot = ft_strrchr(filename, '.');
	if (dot && (ft_strcmp(dot, ".cub") == 0))
		return (true);
	else
		return (false);
}

static bool	check_input(int argc, char **argv)
{
	if (argc != 2 || !argv[1])
		return (print_error("correct usage: <./executable> <map.cub>"), false);
	if (!is_cub_file(argv[1]))
		return (print_error("file must be a .cub extension"), false);
	return (true);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (!check_input(argc, argv))
		return (1);
	init_game(&game);
	if (!parse_cub_file(argv[1], &game.map))
		return (print_map_data(&game.map), free_game(&game), 1);
	print_map_data(&game.map);
	load_in_images(&game);
	free_game(&game);
	return (0);
}
