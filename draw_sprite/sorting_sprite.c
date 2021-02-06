/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_sprite.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 12:21:12 by scolen            #+#    #+#             */
/*   Updated: 2021/02/06 14:34:55 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"

static  void bubble_position_sprite(t_object_on_scene *objects, int i, int j)
{
  float tmp;
  float position;

    tmp = 0;
    position = 0;
    tmp = objects->struct_array[j].distance;
    objects->struct_array[j].distance = objects->struct_array[i].distance;
    objects->struct_array[i].distance = tmp;
    position = objects->pos_sprite_x[i];
    objects->pos_sprite_x[i] = objects->pos_sprite_x[j];
    objects->pos_sprite_x[j] = position;
    position = objects->pos_sprite_y[i];
    objects->pos_sprite_y[i] = objects->pos_sprite_y[j];
    objects->pos_sprite_y[j] = position;
}

void  sorting_sprite(t_object_on_scene *objects)
{
  int i;
  int j;

  i = 0;
  j = 0;
  while (i < objects->quantity_sprite)
  {
    while (j < objects->quantity_sprite)
    {
      if (objects->struct_array[i].distance > objects->struct_array[j].distance)
      {
        bubble_position_sprite(objects, i, j);
      }
      j++;
    }
    j = 0;
    i++;
  }
}
