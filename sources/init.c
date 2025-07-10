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

// TODO	init keys, init mouse, init screen buffer, init player

static void	init_mlx(t_game *game)
{
	printf(BOLD_BLUE"Initializing MLX\n"RESET);
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		print_error("could not initialize MLX");
		exit(1);
	}
	game->window = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (!game->window)
	{
		free_mlx(game);
		print_error("could not create a window");
		exit(1);
	}
}

static bool	init_images(t_game *game)
{
	game->images = malloc(sizeof(t_image));
	if (!game->images)
		return (print_error("could not allocate memory for images"), false);
	game->images->no_img = NULL;
	game->images->so_img = NULL;
	game->images->we_img = NULL;
	game->images->ea_img = NULL;
	return (true);
}

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

bool	init_game(t_game *game)
{
	printf(BOLD_BLUE"Initializing game\n"RESET);

	init_mlx(game);
	if (!init_images(game))
		return (false);
	init_map(game);
	return (true);
}
