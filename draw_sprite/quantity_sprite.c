/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quantity_sprite.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 13:42:16 by scolen            #+#    #+#             */
/*   Updated: 2021/02/06 14:26:02 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"

void	quantity_sprite1(t_object_on_scene *objects)
{
	int i;
	int j;
	int quantity_sprite;

	i = 0;
	j = 0;
	quantity_sprite = 0;
	while (objects->map[i] != NULL)
	{
		while (objects->map[i][j] != '\0')
		{
			if (objects->map[i][j] == '2')
				quantity_sprite++;
			j++;
		}
		j = 0;
		i++;
	}
	objects->quantity_sprite = quantity_sprite;
	malloc_array_sprite(objects);
	search_sprite(objects);
}
