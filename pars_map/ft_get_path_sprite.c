/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_path_sprite.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 12:06:24 by scolen            #+#    #+#             */
/*   Updated: 2021/02/06 22:23:09 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube_three_d.h"

void	get_path_sprite(char *line, t_value_from_map *value_map)
{
	char		*substr;
	int			start;
	static int	quantity_s = 0;

	substr = ft_strnstr(line, "S", ft_strlen(line));
	start = 0;
	if (NULL != substr && ft_strncmp(substr, "S", 2))
	{
		quantity_s++;
		if (quantity_s == 2)
		{
			start = start + 2;
			while (substr[start] == ' ' && substr[start])
				start++;
			value_map->sprite_texture = ft_strdup(&substr[start]);
			while (substr[start] != ' ' && substr[start]
				!= '\t' && substr[start])
				start++;
		}
		else if (quantity_s > 2)
			value_map->sprite_texture = NULL;
	}
}
