#include "../includes/cub3D.h"

bool	is_empty_line(const char *line)
{
	if (!line)
		return (true);
	while (*line)
	{
		if (!ft_isspace(*line))
			return (false);
		line++;
	}
	return (true);
}

char	*skip_leading_whitespaces(const char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	return ((char *)line);
}

void print_map_data(t_map *data)
{
    if (!data)
    {
        print_error("nNo map data to print");
        return;
    }
    // Print configuration
    printf("=== Map Configuration ===\n");
    printf("North Texture: %s\n", data->no_texture ? data->no_texture : "NULL");
    printf("South Texture: %s\n", data->so_texture ? data->so_texture : "NULL");
    printf("West Texture: %s\n", data->we_texture ? data->we_texture : "NULL");
    printf("East Texture: %s\n", data->ea_texture ? data->ea_texture : "NULL");
    printf("Floor Color: %d\n", data->floor_color);
    printf("Ceiling Color: %d\n", data->ceiling_color);
    // Print map info
    printf("\n=== Map Content ===\n");
    printf("Map Dimensions: %dx%d\n", data->width, data->height);
    // Print the map with borders for better visibility
	printf("\n");
	for (int y = 0; y < data->height; y++)
	{
		printf("%3d | ", y);  // Print row number
		for (int x = 0; x < data->width; x++)
		{
			if (x < (int)ft_strlen(data->data[y]))
				printf("%c", data->data[y][x]);
			else
				printf(" ");  // Padding for rectangular maps
		}
		printf("\n");
	}
	printf("\n");
}

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
