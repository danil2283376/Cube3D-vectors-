/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_path_east.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 12:08:30 by scolen            #+#    #+#             */
/*   Updated: 2021/02/06 22:22:58 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube_three_d.h"

void	get_path_east(char *line, t_value_from_map *value_map)
{
	char		*substr;
	int			start;
	static int	quantity_ea = 0;

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
			value_map->east_texture = ft_strdup(&substr[start]);
			while (substr[start] != ' ' && substr[start]
				!= '\t' && substr[start])
				start++;
		}
		else
			value_map->east_texture = NULL;
	}
}
