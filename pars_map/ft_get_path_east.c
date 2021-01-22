/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_path_east.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 12:08:30 by scolen            #+#    #+#             */
/*   Updated: 2021/01/06 11:38:23 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/Users/scolen/cube3D/cube3D.h"

void	get_path_east(char *line, t_value_from_map *value_map)
{
	char *substr;
	int start;
	static int quantity_ea = 0;

	substr = ft_strnstr(line, "EA", ft_strlen(line));
	start = 0;
	if (NULL != substr && ft_strncmp(substr, "EA", 3))
	{
		quantity_ea++;
		if (quantity_ea == 1)
		{
			start = start + 2;
			while (substr[start] == ' ' && substr[start])
				start++;
			value_map->east_texture = ft_strdup(&substr[start]); // MALLOC!
			while (substr[start] != ' ' && substr[start]
				!= '\t' && substr[start])
				start++;
			if (substr[start] == ' ' || substr[start] == '\t')
				value_map->east_texture = NULL;
		}
		else
			value_map->east_texture = NULL;
	}
	// return (quantity_ea);
}
