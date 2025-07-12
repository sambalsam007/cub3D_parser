#include "../includes/cub3D.h"
/*
bool	is_map_line(const char *line)
{
	line = skip_leading_whitespaces(line);
	if (!line || is_empty_line(line))
		return (false);
	while (*line)
	{
		if (!ft_strchr(" 01NSEW", *line) && *line != '\n' && *line != '\r')
			return (false);
		line++;
	}
	return (true);
}

char	*replace_tabs(const char *line)
{
	int		new_len = 0;
	char	*result;
	int		i, j;

	if (!line)
		return (NULL);

	// Calculate new length
	for (i = 0; line[i]; i++)
		new_len += (line[i] == '\t') ? TAB_WIDTH : 1;

	result = malloc(new_len + 1);
	if (!result)
		return (NULL);

	// Copy line, replacing tabs
	for (i = 0, j = 0; line[i]; i++)
	{
		if (line[i] == '\t')
		{
			for (int k = 0; k < TAB_WIDTH; k++)
				result[j++] = ' ';
		}
		else
			result[j++] = line[i];
	}
	result[j] = '\0';
	return (result);
}


static bool	is_config_line(const char *line)
{
	line = skip_leading_whitespaces(line);
	if (!line || is_empty_line(line))
		return (false);
	if ((ft_strncmp(line, "NO", 2) == 0 && (line[2] == ' ' || line[2] == '\t')) ||
		(ft_strncmp(line, "SO", 2) == 0 && (line[2] == ' ' || line[2] == '\t')) ||
		(ft_strncmp(line, "WE", 2) == 0 && (line[2] == ' ' || line[2] == '\t')) ||
		(ft_strncmp(line, "EA", 2) == 0 && (line[2] == ' ' || line[2] == '\t')) ||
		(ft_strncmp(line, "F", 1) == 0 && (line[1] == ' ' || line[1] == '\t')) ||
		(ft_strncmp(line, "C", 1) == 0 && (line[1] == ' ' || line[1] == '\t')))
	{
		return (true);
	}
	return (false);
}

int	parse_rgb(const char *str)
{
	char	**parts;
	int		r;
	int		g;
	int		b;
	int		result;

	parts = ft_split(str, ',');
	if (!parts)
		return (print_error("memory allocation rgb values"), -1);
	if (ft_arrlen(parts) != 3)
		return (print_error("RGB format should be R,G,B"),
					ft_freearr(parts), -1);
	r = ft_atoi(parts[0]);
	g = ft_atoi(parts[1]);
	b = ft_atoi(parts[2]);
	ft_freearr(parts);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (print_error("RBG values should be between [0,255]"), -1);
	result = (r << 16) | (g << 8) | b;
	return (result);
}

void	parse_config_line(t_map *map, const char *line)
{
	line = skip_leading_whitespaces(line);

	if (ft_strncmp(line, "NO", 2) == 0)
		map->no_texture = ft_trim(line + 2);
	else if (ft_strncmp(line, "SO", 2) == 0)
		map->so_texture = ft_trim(line + 2);
	else if (ft_strncmp(line, "WE", 2) == 0)
		map->we_texture = ft_trim(line + 2);
	else if (ft_strncmp(line, "EA", 2) == 0)
		map->ea_texture = ft_trim(line + 2);
	else if (ft_strncmp(line, "F", 1) == 0)
		map->floor_color = parse_rgb(line + 1);
	else if (ft_strncmp(line, "C", 1) == 0)
		map->ceiling_color = parse_rgb(line + 1);
}

bool	validate_map(t_map *map)
{
	if (map->height <= 2 || map->width <= 2)
		return (print_error("invalid map height or width"), false);
	if (map->floor_color == -1 || map->ceiling_color == -1)
		return (false);
	if (!check_single_player(map))
		return (false);
	if (!is_map_enclosed(map))
		return (false);
	return (true);
}

bool	parse_map_content(t_map *map, char **lines, int start_index, int line_count)
{
	// Count map lines first
	int	map_height;
	int	map_index;
	int	i;

	map_height = 0;
	map_index = 0;
	i = start_index;
	while (i < line_count)
	{
		if (!is_map_line(lines[i]))
			return (print_error("map can only contain whitespaces and \"01NSEW\""), false);
    	if (!is_empty_line(lines[i]))
			map_height++;
		i++;
	}
	// Allocate and fill map
    map->data = malloc(sizeof(char *) * (map_height + 1));
	if (!map->data)
		return (print_error("failure mallocing map data"), false);
    i = start_index;
	while (i < line_count && is_map_line(lines[i]))
	{
		if (!is_empty_line(lines[i]))
		{
			map->data[map_index] = ft_strdup(lines[i]);
			if (!map->data[map_index])
				return (ft_freearr(map->data), false);
			map_index++;
		}
		i++;
	}
    map->data[map_height] = NULL;
    map->height = map_height;
	// Find max width
	i = 0;
    while (i < map_height)
	{
        int len = ft_strlen(map->data[i]);
        if (len > map->width)
            map->width = len;
		i++;
	}
    return (validate_map(map));
}

int	parse_configuration(t_map *map, char **lines, int line_count)
{
	int		i = 0;
	bool	map_started = false;
	bool	has_no = false, has_so = false, has_we = false, has_ea = false;
	bool	has_f = false, has_c = false;

	while (i < line_count)
	{
		char *trimmed = skip_leading_whitespaces(lines[i]);

		if (is_empty_line(trimmed))
		{
			i++;
			continue;
		}
		if (is_map_line(trimmed))
		{
		    if (!has_no || !has_so || !has_we || !has_ea || !has_f || !has_c)
        	{
				return (print_error("map content started before all configs were provided"), -1);
			}
			map_started = true;
			break ;
		}
		else if (is_config_line(trimmed))
		{
			if (map_started)
				return (print_error("configuration line after map content has started"), -1);
			if (ft_strncmp(trimmed, "NO", 2) == 0)
			{
	    		if (has_no)
        			return (print_error("duplicate NO texture entry"), -1);
    			has_no = true;
			}
			else if (ft_strncmp(trimmed, "EA", 2) == 0)
			{
	    		if (has_ea)
        			return (print_error("duplicate EA texture entry"), -1);
    			has_ea = true;
			}
			else if (ft_strncmp(trimmed, "SO", 2) == 0)
			{
	    		if (has_so)
        			return (print_error("duplicate SO texture entry"), -1);
    			has_so = true;
			}
			else if (ft_strncmp(trimmed, "WE", 2) == 0)
			{
	    		if (has_we)
        			return (print_error("duplicate WE texture entry"), -1);
    			has_we = true;
			}
			else if (ft_strncmp(trimmed, "F", 1) == 0)
			{
	    		if (has_f)
        			return (print_error("duplicate F texture entry"), -1);
    			has_f = true;
			}
			else if (ft_strncmp(trimmed, "C", 1) == 0)
			{
	    		if (has_c)
        			return (print_error("duplicate C texture entry"), -1);
    			has_c = true;
			}
			parse_config_line(map, trimmed);
		}
		else
			return (printf(BOLD_RED"Error:\nunrecognized line in .cub file; ,,%s'' make sure each element is seperated from information\n"RESET, lines[i]), -1);
		i++;
	}
	if (!map_started)
		return (print_error("map content not found in file"), -1);
	if (!has_no || !has_so || !has_we || !has_ea || !has_f || !has_c)
		return (print_error("missing configuration element(s)"), -1);
	return (i);
}

int		read_file_lines(const char *filename, char ***lines)
{
	int		fd;
	int		line_count;
	char	*line;
	char	**temp;
	char	**new_temp;
	int		capacity;
	int		old_capacity;
	char	*untabbed;

	printf(BOLD_BLUE"Reading file...\n"RESET);
	capacity = FILE_LINE_CAP;
	line_count = 0;
	old_capacity = 0;
	temp = NULL;
	new_temp = NULL;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (print_error("reading in file"), -1);
	temp = malloc(sizeof (char *) * capacity);
	if (!temp)
		return (close(fd), print_error("memory allocation failed for map lines"), -1);
	while ((line = get_next_line(fd)) != NULL)
	{
		//replace tabs with 4 spaces
		untabbed = replace_tabs(line);
		free(line);
		line = untabbed;
		// Strip trailing \n and \r
		size_t len = ft_strlen(line);
		while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r'))
			line[--len] = '\0';
		temp[line_count++] = line;
		// resize if needed
		if (line_count >= capacity)
		{
			old_capacity = capacity * sizeof (char *);
			capacity *= 2;
			new_temp = ft_realloc(temp, old_capacity, sizeof (char *) * capacity);
			if (!new_temp)
				return (ft_freearr(temp), free(line),
					print_error("memory allocation failed for new map lines"), close(fd), -1);
			temp = new_temp;
		}
	}
	// shrink to exact size
	old_capacity = capacity * sizeof (char *);
	new_temp = ft_realloc(temp, old_capacity, sizeof (char *) * (line_count + 1));
	if (!new_temp && line_count > 0)
		return (ft_freearr(temp), close(fd), print_error("memory allocation failed for new temp map lines"),
			-1);
	temp = new_temp;
	temp[line_count] = NULL;
	*lines = temp;
	close(fd);
	return (line_count);
}

bool	parse_cub_file(const char *filename, t_map *map)
{
	char	**lines;
	int		line_count;
	int		map_start;

	printf(BOLD_BLUE"Parsing map file...\n"RESET);
	line_count = read_file_lines(filename, &lines);
	map_start = parse_configuration(map, lines, line_count);
	if (line_count < 0)
		return (ft_freearr(lines), false);
	if (map_start < 0)
		return (ft_freearr(lines), false);
    if (!parse_map_content(map, lines, map_start, line_count))
		return (ft_freearr(lines), false);
	return (ft_freearr(lines), true);
}
*/

bool	is_map_line(const char *line)
{
	line = skip_leading_whitespaces(line);
	if (!line || is_empty_line(line))
		return (false);
	while (*line)
	{
		if (!ft_strchr(" 01NSEW", *line)
			&& *line != '\n' && *line != '\r')
			return (false);
		line++;
	}
	return (true);
}

char	*replace_tabs(const char *line)
{
	int		new_len = 0;
	char	*result;
	int		i = -1, j = 0, k;

	if (!line)
		return (NULL);
	while (line[++i])
		new_len += (line[i] == '\t') ? TAB_WIDTH : 1;
	result = malloc(new_len + 1);
	if (!result)
		return (NULL);
	i = -1;
	while (line[++i])
	{
		if (line[i] == '\t')
		{
			k = -1;
			while (++k < TAB_WIDTH)
				result[j++] = ' ';
		}
		else
			result[j++] = line[i];
	}
	result[j] = '\0';
	return (result);
}

static bool	is_config_line(const char *line)
{
	line = skip_leading_whitespaces(line);
	if (!line || is_empty_line(line))
		return (false);
	if ((ft_strncmp(line, "NO", 2) == 0 && ft_isspace(line[2]))
		|| (ft_strncmp(line, "SO", 2) == 0 && ft_isspace(line[2]))
		|| (ft_strncmp(line, "WE", 2) == 0 && ft_isspace(line[2]))
		|| (ft_strncmp(line, "EA", 2) == 0 && ft_isspace(line[2]))
		|| (ft_strncmp(line, "F", 1) == 0 && ft_isspace(line[1]))
		|| (ft_strncmp(line, "C", 1) == 0 && ft_isspace(line[1])))
		return (true);
	return (false);
}

int	parse_rgb(const char *str)
{
	char	**parts;
	int		r, g, b;

	parts = ft_split(str, ',');
	if (!parts)
		return (print_error("memory allocation rgb values"), -1);
	if (ft_arrlen(parts) != 3)
		return (print_error("RGB format should be R,G,B"),
			ft_freearr(parts), -1);
	r = ft_atoi(parts[0]);
	g = ft_atoi(parts[1]);
	b = ft_atoi(parts[2]);
	ft_freearr(parts);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (print_error("RGB values should be between [0,255]"), -1);
	return ((r << 16) | (g << 8) | b);
}

void	parse_config_line(t_map *map, const char *line)
{
	line = skip_leading_whitespaces(line);
	if (ft_strncmp(line, "NO", 2) == 0)
		map->no_texture = ft_trim(line + 2);
	else if (ft_strncmp(line, "SO", 2) == 0)
		map->so_texture = ft_trim(line + 2);
	else if (ft_strncmp(line, "WE", 2) == 0)
		map->we_texture = ft_trim(line + 2);
	else if (ft_strncmp(line, "EA", 2) == 0)
		map->ea_texture = ft_trim(line + 2);
	else if (ft_strncmp(line, "F", 1) == 0)
		map->floor_color = parse_rgb(line + 1);
	else if (ft_strncmp(line, "C", 1) == 0)
		map->ceiling_color = parse_rgb(line + 1);
}

bool	validate_map(t_map *map)
{
	if (map->height <= 2 || map->width <= 2)
		return (print_error("invalid map height or width"), false);
	if (map->floor_color == -1 || map->ceiling_color == -1)
		return (false);
	if (!check_single_player(map) || !is_map_enclosed(map))
		return (false);
	return (true);
}

static void	set_dimensions(t_map *map)
{
	int	len;
	int	i = -1;

	while (map->data[++i])
	{
		len = ft_strlen(map->data[i]);
		if (len > map->width)
			map->width = len;
	}
}

bool	parse_map_content(t_map *map, char **lines, int start, int total)
{
	int	i = start, h = 0, idx = 0;

	while (i < total)
	{
		if (!is_map_line(lines[i]))
			return (print_error("invalid map line"), false);
		if (!is_empty_line(lines[i]))
			h++;
		i++;
	}
	map->data = malloc(sizeof(char *) * (h + 1));
	if (!map->data)
		return (print_error("malloc map data"), false);
	i = start;
	while (i < total && is_map_line(lines[i]))
	{
		if (!is_empty_line(lines[i]))
		{
			map->data[idx] = ft_strdup(lines[i]);
			if (!map->data[idx++])
				return (ft_freearr(map->data), false);
		}
		i++;
	}
	map->data[h] = NULL;
	map->height = h;
	set_dimensions(map);
	return (validate_map(map));
}

int	parse_configuration(t_map *map, char **lines, int total)
{
	int						i = 0;
	bool					has[6] = {0};
	bool					map_started = false;

	while (i < total)
	{
		char *trimmed = skip_leading_whitespaces(lines[i]);
		if (is_empty_line(trimmed))
			{ i++; continue; }
		if (is_map_line(trimmed))
		{
			if (!has[0] || !has[1] || !has[2] || !has[3] || !has[4] || !has[5])
				return (print_error("map before configs"), -1);
			map_started = true;
			break ;
		}
		if (is_config_line(trimmed))
		{
			if (map_started)
				return (print_error("config after map started"), -1);
			if (ft_strncmp(trimmed, "NO", 2) == 0 && has[0]++)
				return (print_error("duplicate NO"), -1);
			if (ft_strncmp(trimmed, "SO", 2) == 0 && has[1]++)
				return (print_error("duplicate SO"), -1);
			if (ft_strncmp(trimmed, "WE", 2) == 0 && has[2]++)
				return (print_error("duplicate WE"), -1);
			if (ft_strncmp(trimmed, "EA", 2) == 0 && has[3]++)
				return (print_error("duplicate EA"), -1);
			if (ft_strncmp(trimmed, "F", 1) == 0 && has[4]++)
				return (print_error("duplicate F"), -1);
			if (ft_strncmp(trimmed, "C", 1) == 0 && has[5]++)
				return (print_error("duplicate C"), -1);
			parse_config_line(map, trimmed);
		}
		else
			return (print_error("unrecognized line"), -1);
		i++;
	}
	if (!map_started)
		return (print_error("map not found"), -1);
	return (i);
}

int	read_file_lines(const char *filename, char ***lines)
{
	int		fd, count = 0, cap = FILE_LINE_CAP;
	char	*line, *untab;
	char	**temp, **resized;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (print_error("reading file"), -1);
	temp = malloc(sizeof(char *) * cap);
	if (!temp)
		return (close(fd), print_error("malloc fail"), -1);
	while ((line = get_next_line(fd)))
	{
		untab = replace_tabs(line);
		free(line);
		line = untab;
		while (line && ft_strlen(line) &&
			(line[ft_strlen(line) - 1] == '\n'
			|| line[ft_strlen(line) - 1] == '\r'))
			line[--ft_strlen(line)] = '\0';
		temp[count++] = line;
		if (count >= cap)
		{
			resized = ft_realloc(temp, sizeof(char *) * cap,
				sizeof(char *) * cap * 2);
			if (!resized)
				return (ft_freearr(temp), print_error("realloc fail"), close(fd), -1);
			cap *= 2;
			temp = resized;
		}
	}
	temp[count] = NULL;
	*lines = temp;
	close(fd);
	return (count);
}

bool	parse_cub_file(const char *filename, t_map *map)
{
	char	**lines;
	int		total, start;

	total = read_file_lines(filename, &lines);
	if (total < 0)
		return (false);
	start = parse_configuration(map, lines, total);
	if (start < 0)
		return (ft_freearr(lines), false);
	if (!parse_map_content(map, lines, start, total))
		return (ft_freearr(lines), false);
	return (ft_freearr(lines), true);
}

