/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-rudd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:50:34 by yde-rudd          #+#    #+#             */
/*   Updated: 2025/07/15 10:20:02 by yde-rudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	free_mlx(t_game *game)
{
	printf(BOLD_BLUE"Freeing MLX\n"RESET);
	if (game->window)
		mlx_destroy_window(game->mlx, game->window);
	if (game->mlx)
		mlx_destroy_display(game->mlx);
	free(game->mlx);
}

static void	destroy_images(t_game *game)
{
	if (game->images->no_img)
		mlx_destroy_image(game->mlx, game->images->no_img);
	if (game->images->ea_img)
		mlx_destroy_image(game->mlx, game->images->ea_img);
	if (game->images->so_img)
		mlx_destroy_image(game->mlx, game->images->so_img);
	if (game->images->we_img)
		mlx_destroy_image(game->mlx, game->images->we_img);
	free(game->images);
	game->images = NULL;
}

void	free_game(t_game *game)
{
	printf(BOLD_BLUE"Freeing game\n"RESET);
	ft_freearr(game->map.data);
	if (game->map.no_texture)
		free(game->map.no_texture);
	if (game->map.so_texture)
		free(game->map.so_texture);
	if (game->map.ea_texture)
		free(game->map.ea_texture);
	if (game->map.we_texture)
		free(game->map.we_texture);
	destroy_images(game);
	free_mlx(game);
}
