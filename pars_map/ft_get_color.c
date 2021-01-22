/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 12:14:20 by scolen            #+#    #+#             */
/*   Updated: 2021/01/06 11:38:14 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/Users/scolen/cube3D/cube3D.h"

static int	cont_get_val_color(char *substr, t_value_from_map *value_map,
	int quantity_number, int start)
{
	int number;
	int new_start;
	int count_comma;

	new_start = 0;
	count_comma = 0;
	number = ft_atoi(&substr[new_start]);
	if (quantity_number == 0)
		value_map->ceilling_color_r = number;
	else if (quantity_number == 1)
		value_map->ceilling_color_g = number;
	else if (quantity_number == 2)
		value_map->ceilling_color_b = number;
	new_start = new_start + len_number(number) - 1;
	new_start = new_start + pass_space(&substr[new_start]);
	while (substr[new_start] == ',')
	{
		new_start++;
		count_comma++;
	}
	if (count_comma > 1)
		value_map->ceilling_color_r = -1;
	return (new_start + start);
}

static void	continue_get_val_color(char *substr, t_value_from_map *value_map)
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
		start = cont_get_val_color(&substr[start],
			value_map, quantity_number, start);
		if (substr[start] == ',' && quantity_number < 3)
			start++;
		else if ((substr[start] != ' ' && quantity_number > 2))
		{
			value_map->ceilling_color_r = -1;
			break ;
		}
		quantity_number++;
	}
}

void	get_value_color(char *line, t_value_from_map *value_map)
{
	char		*substr;
	int			start;
	int			number;
	static int	quantity_c = 0;

	substr = ft_strnstr(line, "C", ft_strlen(line));
	start = 0;
	number = 0;
	if (NULL != substr && ft_strncmp(substr, "C", 2))
	{
		quantity_c++;
		if (count_comma(line) == 2)
		{
			if (quantity_c > 1)
				value_map->ceilling_color_r = -1;
			else if (quantity_c == 1)
			{
				start++;
				while (substr[start] == ' ' && substr[start])
					start++;
				continue_get_val_color(&substr[start], value_map);
			}
		}
	}
	// return (quantity_c);
}
