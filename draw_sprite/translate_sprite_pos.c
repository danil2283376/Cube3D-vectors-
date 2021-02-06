/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_sprite_pos.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 21:17:47 by scolen            #+#    #+#             */
/*   Updated: 2021/02/06 22:36:39 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube_three_d.h"

void	translate_sprite_pos(t_object_on_scene *objects, int i)
{
	objects->position_sprite_x = objects->pos_sprite_x[i]
		- objects->player_position_x;
	objects->position_sprite_y = objects->pos_sprite_y[i]
		- objects->player_position_y;
	objects->inverse_matrix = 1.0 /
		(objects->plane_x * objects->player_direction_y
			- objects->player_direction_x * objects->plane_y);
	objects->transform_pos_x = objects->inverse_matrix
		* (objects->player_direction_y
			* objects->position_sprite_x -
				objects->player_direction_x * objects->position_sprite_y);
	objects->transform_pos_y = objects->inverse_matrix * (-objects->plane_y
			* objects->position_sprite_x
				+ objects->plane_x * objects->position_sprite_y);
	objects->screen_pos_x = (int)((objects->s_value_from_map.resolution_x / 2)
			* (1 + objects->transform_pos_x / objects->transform_pos_y));
}
