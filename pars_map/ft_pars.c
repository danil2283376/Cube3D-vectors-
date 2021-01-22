/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 13:15:09 by scolen            #+#    #+#             */
/*   Updated: 2021/01/06 11:39:03 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/Users/scolen/cube3D/cube3D.h"

int	string_from_space(char *line, t_value_from_map *value_map)
{
	int start;
	int len_str;
	int count_space;

	start = 0;
	count_space = 0;
	len_str = ft_strlen(line);
	// printf("str = %s|\n", &line[start]);
	while (line[start] == ' ' || line[start] == '\t')
	{
		count_space++;
		start++;
	}
	if (count_space == len_str && line[start] != '\0'/* || line[start + 1] == '\0')*/)
	{
		printf("HELL");
		standart_value_struct(value_map);
		return (1);
	}
	if (((line[start] == 'R')
		|| (line[start] == 'N' && line[start + 1] == 'O')
		|| (line[start] == 'S' && line[start + 1] == 'O')
		|| (line[start] == 'W' && line[start + 1] == 'E')
		|| (line[start] == 'E' && line[start + 1] == 'A')
		|| (line[start] == 'S') || (line[start] == 'C')
		|| (line[start] == 'F')) && line[start] == '\0')
		{
			// printf("SHIT, str = %s\n", &line[start]);
			return (0);
		}
	if (count_space > 0 || (line[start] != '\0' && (line[start] != 'R'
		&& (line[start] != 'N' && line[start + 1] != 'O')
		&& (line[start] != 'S' && line[start + 1] != 'O')
		&& (line[start] != 'W' && line[start + 1] != 'E')
		&& (line[start] != 'E' && line[start + 1] != 'A')
		&& (line[start] != 'S') && (line[start] != 'C')
		&& (line[start] != 'F'))))
		{
			// standart_value_struct(value_map);
		return (1);
		}
	// printf("SHIT, str = %s\n", &line[start]);
	return (0);
}

int		is_map(char *line)
{
	int start;

	start = 0;
	while (line[start] == ' ' || line[start] == '\t')
		line++;
	if (line[start] == '1' || line[start] == '0')
	{
		return (1);
	}
	else
	{
		// printf("str = %s\n", line);
		return (0);
	}
}

char	*threatment_map(char *line, char *map, t_value_from_map *value_map)
{
	int line_start;
	(void)value_map;
	char *new_line;

	line_start = 0;
	new_line = ft_strdup(line);
	while (new_line[line_start] == '\t' || new_line[line_start] == ' ')
		line_start++;
	while (new_line[line_start])
		line_start++;
	new_line[line_start] = '*';
	new_line[line_start + 1] = '\0';
	line_start = 0;
		map = ft_strjoin(map, new_line);
	return (map);
}

char	**manage_function(int fd, t_value_from_map *value_map)
{
	char *line;
	int is_map1;
	char *map;
	char **matrix_map;
	char *ptr;

	is_map1 = 0;
	map = ft_strdup("");
	while (get_next_line(fd, &line))
	{
		is_map1 = is_map(line);
		if ((is_map1 == 0) && string_from_space(line, value_map) == 1)
		{
			standart_value_struct(value_map);
			free(line);
			return (NULL);
		}
		get_value_resolution(line, value_map);
		get_path_north(line, value_map);
		get_path_south(line, value_map);
		get_path_west(line, value_map);
		get_path_east(line, value_map);
		get_path_sprite(line, value_map);
		get_value_color(line, value_map);
		get_value_color_floor(line, value_map);
		if (is_map1 == 1)
		{
			ptr = map;
			map = threatment_map(line, map, value_map);
			free(ptr);
		}
		free(line);
	}
	return (matrix_map = ft_split(map, '*'));
	// printf("Resolution: x = %d, y = %d\n", value_map->resolution_x, value_map->resolution_y);
	// printf("North = %s\n", value_map->north_texture);
	// printf("South = %s\n", value_map->south_texture);
	// printf("West = %s\n", value_map->west_texture);
	// printf("East = %s\n", value_map->east_texture);
	// printf("Sprite = %s\n", value_map->sprite_texture);
	// printf("Color_r = %d\n", value_map->ceilling_color_r);
	// printf("Color_g = %d\n", value_map->ceilling_color_g);
	// printf("Color_b = %d\n", value_map->ceilling_color_b);
	// printf("Floor_r = %d\n", value_map->floor_color_r);
	// printf("Floor_g = %d\n", value_map->floor_color_g);
	// printf("Floor_b = %d\n", value_map->floor_color_b);
}
