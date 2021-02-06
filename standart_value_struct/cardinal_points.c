/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cardinal_points.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 12:04:18 by scolen            #+#    #+#             */
/*   Updated: 2021/02/06 12:04:24 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"

void  cardinal_points(t_object_on_scene *objects)
{
  if (objects->cardinal_point == 'N') // смотрит вверх
  {
    objects->player_direction_x = -1;
    objects->planeY = 0.66;
  }
  if (objects->cardinal_point == 'S') // смотрит вниз
  {
    objects->player_direction_x = 1;
    objects->planeY = -0.66;
  }
  if (objects->cardinal_point == 'W') // смотрет влево
  {
    objects->player_direction_y = -1;
    objects->planeX = -0.66;
  }
  if (objects->cardinal_point == 'E') // смотрит вправо
  {
    objects->player_direction_y = 1;
    objects->planeX = 0.66;
  }
}
