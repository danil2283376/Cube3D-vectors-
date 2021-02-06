/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_path_west.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 12:10:58 by scolen            #+#    #+#             */
/*   Updated: 2021/02/06 22:23:12 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube_three_d.h"

void	get_path_west(char *line, t_value_from_map *value_map)
{
	char		*substr;
	int			start;
	static int	quantity_we = 0;

	substr = ft_strnstr(line, "WE", ft_strlen(line));
	start = 0;
	if (NULL != substr && ft_strncmp(substr, "WE", 3))
	{
		quantity_we++;
		if (quantity_we == 1)
		{
			start = start + 2;
			while (substr[start] == ' ' && substr[start])
				start++;
			value_map->west_texture = ft_strdup(&substr[start]);
			while (substr[start] != ' ' && substr[start]
				!= '\t' && substr[start])
				start++;
		}
		else
			value_map->west_texture = NULL;
	}
}
