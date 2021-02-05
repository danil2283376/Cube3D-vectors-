/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_sprite_pos.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 21:17:47 by scolen            #+#    #+#             */
/*   Updated: 2021/02/05 21:20:44 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"

void	translate_sprite_pos(t_object_on_scene *objects, int i)
{
	/*double spriteX*/objects->position_sprite_x = objects->pos_sprite_x[i] - objects->player_position_x;
      /*double spriteY*/objects->position_sprite_y = objects->pos_sprite_y[i] - objects->player_position_y;

      /*double invDet*/objects->inverse_matrix = 1.0 / (objects->planeX * objects->player_direction_y - objects->player_direction_x * objects->planeY); //required for correct matrix multiplication

      /*double transformX*/objects->transform_pos_x = objects->inverse_matrix * (objects->player_direction_y * objects->position_sprite_x - objects->player_direction_x * objects->position_sprite_y);
      /*double transformY*/objects->transform_pos_y = objects->inverse_matrix * (-objects->planeY * objects->position_sprite_x + objects->planeX * objects->position_sprite_y); //this is actually the depth inside the screen, that what Z is in 3D

      /*int spriteScreenX*/objects->screen_pos_x = (int)((objects->s_value_from_map.resolution_x / 2) * (1 + objects->transform_pos_x / objects->transform_pos_y));
}
