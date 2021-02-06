/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_path_south.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 12:12:01 by scolen            #+#    #+#             */
/*   Updated: 2021/02/06 22:23:05 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube_three_d.h"

void	get_path_south(char *line, t_value_from_map *value_map)
{
	char		*substr;
	int			start;
	static int	quantity_so = 0;

	substr = ft_strnstr(line, "SO", ft_strlen(line));
	start = 0;
	if (NULL != substr && ft_strncmp(substr, "SO", 3))
	{
		quantity_so++;
		if (quantity_so == 1)
		{
			start = start + 2;
			while (substr[start] == ' ' && substr[start])
				start++;
			value_map->south_texture = ft_strdup(&substr[start]);
			while (substr[start] != ' ' && substr[start]
				!= '\t' && substr[start])
				start++;
		}
		else
			value_map->south_texture = NULL;
	}
}
