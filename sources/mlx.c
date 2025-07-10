#include "../includes/cub3D.h"

void	load_in_images(t_game *game)
{
	int	width;
	int	height;

	printf(BOLD_BLUE"Loading in MLX images...\n"RESET);
	game->images->no_img = mlx_xpm_file_to_image(game->mlx, game->map.no_texture, &width, &height);
	if (!game->images->no_img)
		return (print_error("failed to load in NO texture"));
	game->images->ea_img = mlx_xpm_file_to_image(game->mlx, game->map.ea_texture, &width, &height);
	if (!game->images->ea_img)
		return (print_error("failed to load in EA texture"));
	game->images->so_img = mlx_xpm_file_to_image(game->mlx, game->map.so_texture, &width, &height);
	if (!game->images->so_img)
		return (print_error("failed to load in SO texture"));
	game->images->we_img = mlx_xpm_file_to_image(game->mlx, game->map.we_texture, &width, &height);
	if (!game->images->we_img)
		return (print_error("failed to load in WE texture"));
}
