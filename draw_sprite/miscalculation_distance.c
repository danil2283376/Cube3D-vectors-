/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miscalculation_distance.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 12:19:51 by scolen            #+#    #+#             */
/*   Updated: 2021/02/06 22:21:57 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube_three_d.h"

void	miscalculation_distance(t_object_on_scene *objects)
{
	int i;

	i = 0;
	while (i < objects->quantity_sprite)
	{
		objects->struct_array[i].distance = ((objects->player_position_x
			- objects->pos_sprite_x[i])
			* (objects->player_position_x - objects->pos_sprite_x[i])
			+ (objects->player_position_y - objects->pos_sprite_y[i])
			* (objects->player_position_y - objects->pos_sprite_y[i]));
		i++;
	}
}
