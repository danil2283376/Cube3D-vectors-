/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 16:58:22 by scolen            #+#    #+#             */
/*   Updated: 2021/02/06 14:44:19 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"

void	calculate_side_dst(t_object_on_scene *objects)
{
	if(objects->rdx < 0)
    {
      objects->step_x = -1;
      objects->side_dist_x = (objects->player_position_x - objects->posmapx) * objects->del_dis_x;
    }
    else
    {
      objects->step_x = 1;
      objects->side_dist_x = (objects->posmapx + 1.0 - objects->player_position_x) * objects->del_dis_x;
    }
    if(objects->rdy < 0)
    {
      objects->step_y = -1;
      objects->side_dist_y = (objects->player_position_y - objects->posmapy) * objects->del_dis_y;
    }
    else
    {
      objects->step_y = 1;
      objects->side_dist_y = (objects->posmapy + 1.0 - objects->player_position_y) * objects->del_dis_y;
    }
}

void	algoritm_dda(t_object_on_scene *objects)
{
	while (objects->hit == 0)
  {
    if (objects->side_dist_x < objects->side_dist_y)
    {
      objects->side_dist_x += objects->del_dis_x;
      objects->posmapx += objects->step_x;
      objects->side = 0;
    }
    else
    {
      objects->side_dist_y += objects->del_dis_y;
      objects->posmapy += objects->step_y;
      objects->side = 1;
    }
    if (objects->map[objects->posmapx][objects->posmapy] == '1')
      objects->hit = 1;
  }
}

void	raycast(t_object_on_scene *objects, int x)
{

    objects->pos_camera_x = 2 * x / (double)objects->s_value_from_map.resolution_x - 1; //x-coordinate in camera space
    objects->rdx = objects->player_direction_x + objects->planeX * objects->pos_camera_x;
    objects->rdy = objects->player_direction_y + objects->planeY * objects->pos_camera_x;
    objects->posmapx = (int)(objects->player_position_x);
    objects->posmapy = (int)(objects->player_position_y);
    objects->del_dis_x = sqrt(1 + (objects->rdy * objects->rdy) / (objects->rdx * objects->rdx));
    objects->del_dis_y = sqrt(1 + (objects->rdx * objects->rdx) / (objects->rdy * objects->rdy));
    objects->hit = 0;
	  calculate_side_dst(objects);
	  algoritm_dda(objects);
}
