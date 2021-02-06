/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_sprite_in_map.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 13:47:05 by scolen            #+#    #+#             */
/*   Updated: 2021/02/06 22:22:09 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube_three_d.h"

void	search_sprite(t_object_on_scene *objects)
{
	int i;
	int j;
	int count;

	i = 0;
	j = 0;
	count = 0;
	while (objects->map[i] != NULL)
	{
		while (objects->map[i][j] != '\0')
		{
			if (objects->map[i][j] == '2')
			{
				objects->pos_sprite_x[count] = i + 0.5f;
				objects->pos_sprite_y[count] = j + 0.5f;
				count++;
			}
			j++;
		}
		j = 0;
		i++;
	}
}
