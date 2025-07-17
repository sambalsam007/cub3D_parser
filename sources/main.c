/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-rudd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:47:17 by yde-rudd          #+#    #+#             */
/*   Updated: 2025/07/15 10:10:35 by yde-rudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

/* is_cub_file: 
 * */

static bool	is_cub_file(const char *filename)
{
	const char	*dot; // Q: waarom 'dot'?

	dot = ft_strrchr(filename, '.'); // neem enkel de string vanaf '.' (de extensie)
	if (dot && (ft_strcmp(dot, ".cub") == 0))
		return (true);
	else
		return (false);
}

/* check_input: "Makkik binnen" 
 * is er 1 parameter meegegeven met extensie .cub?
 * return true */

static bool	check_input(int argc, char **argv)
{
	if (argc != 2 || !argv[1]) // het programma moet een map meekrijgen
		return (print_error("correct usage: <./executable> <map.cub>"), false);
	if (!is_cub_file(argv[1])) // de map moet een .cub extensie hebben
		return (print_error("file must be a .cub extension"), false);
	return (true);
}

int	main(int argc, char **argv) // geef het programma een map
{
	t_game	game;

	if (!check_input(argc, argv)) // geen arguments? stop programma
		return (1);
	init_game(&game);
	if (!parse_cub_file(argv[1], &game.map))
		return (print_map_data(&game.map), free_game(&game), 1);
	print_map_data(&game.map);
	if (!load_in_images(&game))
		return (free_game(&game), 1);
	free_game(&game);
	return (0);
}
