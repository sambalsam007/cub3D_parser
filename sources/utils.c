/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-rudd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 09:23:55 by yde-rudd          #+#    #+#             */
/*   Updated: 2025/07/15 10:29:21 by yde-rudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	print_error(char *str)
{
	printf(BOLD_RED"Error:\n"RESET);
	printf(BOLD_RED"%s\n"RESET, str);
}

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

void	print_map_data(t_map *data)
{
	int	y;
	int	x;

	if (!data)
		return (print_error("No map data to print"));
	printf("=== Map Configuration ===\n");
	printf("North Texture: %s\n", data->no_texture);
	printf("South Texture: %s\n", data->so_texture);
	printf("West Texture: %s\n", data->we_texture);
	printf("East Texture: %s\n", data->ea_texture);
	printf("Floor Color: %d\n", data->floor_color);
	printf("Ceiling Color: %d\n", data->ceiling_color);
	printf("\n=== Map Content ===\n");
	printf("Map Dimensions: %dx%d\n", data->width, data->height);
	printf("\n");
	y = 0;
	while (y < data->height)
	{
		x = 0;
		printf("%3d | ", y);
		while (x < data->width)
		{
			if (x < (int)ft_strlen(data->data[y]))
				printf("%c", data->data[y][x]);
			else
				printf(" ");
			x++;
		}
		printf("\n");
		y++;
	}
	printf("\n");
}
