/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pars_color_floor.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 12:32:51 by scolen            #+#    #+#             */
/*   Updated: 2021/02/02 19:26:31 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"

static int	take_number(char *substr, t_value_from_map *value_map,
	int quantity_number, int start)
{
	int number;
	int new_start;
	int count_comma;

	new_start = 0;
	count_comma = 0;
	number = ft_atoi(&substr[new_start]);
	if (quantity_number == 0)
		value_map->floor_color_r = number;
	else if (quantity_number == 1)
		value_map->floor_color_g = number;
	else if (quantity_number == 2)
		value_map->floor_color_b = number;
	new_start = new_start + len_number(number) - 1;
	if (number < 0)
		new_start++;
	new_start = new_start + pass_space(&substr[new_start]);
	while (substr[new_start] == ',')
	{
		new_start++;
		count_comma++;
	}
	if (count_comma > 1)
		value_map->floor_color_r = -1;
	return (new_start + start);
}

static void	continue_get_val_color_floor(char *substr, t_value_from_map *value_map)
{
	int start;
	int quantity_number;
	int quantity_comma;

	start = 0;
	quantity_comma = 0;
	quantity_number = 0;
	while (substr[start])
	{
		start = start + pass_space(&substr[start]);
		while (substr[start] == '0')
			start++;
		start = take_number(&substr[start],
			value_map, quantity_number, start);
		if (substr[start] == ',' && quantity_number < 3)
			start++;
		else if ((substr[start] != ' ' && quantity_number > 2))
		{
			value_map->floor_color_r = -1;
			break ;
		}
		quantity_number++;
	}
}

void	get_value_color_floor(char *line, t_value_from_map *value_map)
{
	char		*substr;
	int			start;
	int			number;
	static int	quantity_f = 0;

	substr = ft_strnstr(line, "F", ft_strlen(line));
	start = 0;
	number = 0;
	if (NULL != substr && ft_strncmp(substr, "F", 2))
	{
		quantity_f++;
		if (count_comma(line) == 2)
		{
			if (quantity_f > 1)
				value_map->floor_color_r = -1;
			else if (quantity_f == 1)
			{
				start++;
				while (substr[start] == ' ' && substr[start])
					start++;
				continue_get_val_color_floor(&substr[start], value_map);
			}
		}
	}
	// return (quantity_f);
}
