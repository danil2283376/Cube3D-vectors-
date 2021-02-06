/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pars_resolution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 11:58:12 by scolen            #+#    #+#             */
/*   Updated: 2021/02/06 22:23:19 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube_three_d.h"

static void	numbers(int quantity_number,
	t_value_from_map *value_map, int number)
{
	if (quantity_number == 0)
		value_map->resolution_x = number;
	else if (quantity_number == 1)
		value_map->resolution_y = number;
	else
		value_map->resolution_x = -1;
}

static void	continue_get_value_resolution(char *substr,
	t_value_from_map *value_map)
{
	int start;
	int number;
	int quantity_number;

	start = 1;
	number = 0;
	quantity_number = 0;
	while (substr[start])
	{
		start = start + pass_space(&substr[start]);
		while (substr[start] == '0')
			start++;
		number = ft_atoi(&substr[start]);
		start = start + len_number(number) - 1;
		if (substr[start] != ' ' && substr[start] != '\t' &&
			!ft_isdigit(substr[start]) && substr[start] != '\0')
		{
			value_map->resolution_x = -1;
			break ;
		}
		numbers(quantity_number, value_map, number);
		quantity_number++;
	}
}

void		get_value_resolution(char *line, t_value_from_map *value_map)
{
	char		*substr;
	int			start;
	int			length_number;
	int			number;
	static int	quantity_r = 0;

	substr = ft_strnstr(line, "R", ft_strlen(line));
	start = 0;
	length_number = 0;
	number = 0;
	if (NULL != substr && ft_strncmp(substr, "R", 2))
	{
		quantity_r++;
		if (quantity_r > 1)
			value_map->resolution_x = -1;
		else if (quantity_r == 1)
			continue_get_value_resolution(&substr[start], value_map);
	}
}
