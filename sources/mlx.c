/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-rudd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 09:23:37 by yde-rudd          #+#    #+#             */
/*   Updated: 2025/07/15 10:31:53 by yde-rudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

bool	load_in_images(t_game *game)
{
	int	width;
	int	height;

	printf(BOLD_BLUE"Loading in MLX images...\n"RESET);
	if (!game->map.so_texture || !game->map.no_texture
		|| !game->map.ea_texture || !game->map.we_texture)
		return (print_error("empty texture found"), false);
	game->images->no_img = mlx_xpm_file_to_image(game->mlx,
			game->map.no_texture, &width, &height);
	if (!game->images->no_img)
		return (print_error("failed to load in NO texture"), false);
	game->images->ea_img = mlx_xpm_file_to_image(game->mlx,
			game->map.ea_texture, &width, &height);
	if (!game->images->ea_img)
		return (print_error("failed to load in EA texture"), false);
	game->images->so_img = mlx_xpm_file_to_image(game->mlx,
			game->map.so_texture, &width, &height);
	if (!game->images->so_img)
		return (print_error("failed to load in SO texture"), false);
	game->images->we_img = mlx_xpm_file_to_image(game->mlx,
			game->map.we_texture, &width, &height);
	if (!game->images->we_img)
		return (print_error("failed to load in WE texture"), false);
	return (true);
}
