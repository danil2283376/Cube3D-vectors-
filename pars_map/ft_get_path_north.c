/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_path_north.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 12:07:26 by scolen            #+#    #+#             */
/*   Updated: 2021/02/06 22:23:02 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube_three_d.h"

void	get_path_north(char *line, t_value_from_map *value_map)
{
	char		*substr;
	int			start;
	static int	quantity_no = 0;

	substr = ft_strnstr(line, "NO", ft_strlen(line));
	start = 0;
	if (NULL != substr && ft_strncmp(substr, "NO", 3))
	{
		quantity_no++;
		if (quantity_no == 1)
		{
			start = start + 2;
			while (substr[start] == ' ' && substr[start])
				start++;
			value_map->north_texture = ft_strdup(&substr[start]);
			while (substr[start] != ' ' && substr[start]
					!= '\t' && substr[start])
				start++;
		}
		else
			value_map->north_texture = NULL;
	}
}
