/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 13:15:09 by scolen            #+#    #+#             */
/*   Updated: 2021/02/06 22:23:23 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube_three_d.h"

int		string_from_space(char *line, t_value_from_map *value_map)
{
	int start;
	int len_str;
	int count_space;

	start = 0;
	count_space = 0;
	len_str = ft_strlen(line);
	while (line[start] == ' ' || line[start] == '\t')
	{
		count_space++;
		start++;
	}
	if (count_space == len_str && line[start] != '\0')
	{
		standart_value_struct(value_map);
		return (1);
	}
	return (return_value(line, start, count_space));
}

int		is_map(char *line)
{
	int start;

	start = 0;
	while (line[start] == ' ' || line[start] == '\t')
		line++;
	if (line[start] == '1' || line[start] == '0')
		return (1);
	else
		return (0);
}

char	*threatment_map(char *line, char *map)
{
	int		line_start;
	char	*new_line;
	char	*leaks;

	line_start = 0;
	new_line = ft_strdup(line);
	while (new_line[line_start] == '\t' || new_line[line_start] == ' ')
		line_start++;
	while (new_line[line_start])
		line_start++;
	leaks = new_line;
	new_line = ft_strjoin(new_line, "*");
	free(leaks);
	line_start = 0;
	leaks = new_line;
	map = ft_strjoin(map, new_line);
	free(leaks);
	return (map);
}

char	*get_value_from_map(char *line, t_value_from_map *value_map,
	t_object_on_scene *objects, char *map)
{
	char *ptr;

	ptr = NULL;
	value_map->is_map = is_map(line);
	get_value_resolution(line, value_map);
	get_path_north(line, value_map);
	get_path_south(line, value_map);
	get_path_west(line, value_map);
	get_path_east(line, value_map);
	if (value_map->is_map == 0)
		get_path_sprite(line, value_map);
	get_value_color(line, value_map);
	get_value_color_floor(line, value_map);
	if (value_map->is_map == 1)
	{
		objects->s_value_from_map.meet_map = 1;
		ptr = map;
		map = threatment_map(line, map);
		free(ptr);
	}
	return (map);
}

char	**manage_function(int fd, t_value_from_map *value_map,
	t_object_on_scene *objects)
{
	char	*line;
	char	*map;

	value_map->is_map = 0;
	map = ft_strdup("");
	while (get_next_line(fd, &line))
	{
		map = get_value_from_map(line, value_map, objects, map);
		if (objects->s_value_from_map.meet_map == 0)
			objects->s_value_from_map.quantity_string_before_map++;
		objects->s_value_from_map.quantity_string_map++;
		free(line);
	}
	if (!(objects->map = ft_split(map, '*')))
		threatment_error(1, "Huge map!", objects);
	free(map);
	free(line);
	return (objects->map);
}
