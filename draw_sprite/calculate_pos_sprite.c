/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_pos_sprite.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 21:21:33 by scolen            #+#    #+#             */
/*   Updated: 2021/02/05 21:23:28 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"

void	calculate_height_sprite(t_object_on_scene *objects)
{
	/*int spriteHeight*/objects->sprite_height = abs((int)(objects->s_value_from_map.resolution_y / (objects->transform_pos_y))); //using 'transformY' instead of the real distance prevents fisheye
      //calculate lowest and highest pixel to fill in current stripe
      /*int drawStartY*/objects->start_sprite_y = -objects->sprite_height / 2 + objects->s_value_from_map.resolution_y / 2;
      if (objects->start_sprite_y < 0) objects->start_sprite_y = 0;
      /*int drawEndY*/objects->end_sprite_y = objects->sprite_height / 2 + objects->s_value_from_map.resolution_y / 2;
      if (objects->end_sprite_y >= objects->s_value_from_map.resolution_y) objects->end_sprite_y = objects->s_value_from_map.resolution_y - 1;
}

void	calculate_width_sprite(t_object_on_scene *objects)
{
	/*int spriteWidth*/objects->width_sprite = abs((int)(objects->s_value_from_map.resolution_y / (objects->transform_pos_y)));
      /*int drawStartX*/objects->start_sprite_x = -objects->width_sprite / 2 + objects->screen_pos_x;
      if(objects->start_sprite_x < 0) objects->start_sprite_x = 0;
      /*int drawEndX*/objects->end_sprite_x = objects->width_sprite / 2 + objects->screen_pos_x;
      if (objects->end_sprite_x >= objects->s_value_from_map.resolution_x) objects->end_sprite_x = objects->s_value_from_map.resolution_x - 1;
}
