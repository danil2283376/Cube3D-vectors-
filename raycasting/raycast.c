/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 16:58:22 by scolen            #+#    #+#             */
/*   Updated: 2021/02/05 20:11:23 by scolen           ###   ########.fr       */
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
      //jump to next map square, OR in x-direction, OR in y-direction
      if (objects->side_dist_x < objects->side_dist_y)
      {
        objects->side_dist_x += objects->del_dis_x;
        objects->posmapx += objects->step_x;
        objects->side = 0; // попадание по Y
      }
      else
      {
        objects->side_dist_y += objects->del_dis_y;
        objects->posmapy += objects->step_y;
        objects->side = 1; // попадание по X
      }
      //Check if ray has hit a wall
      if (objects->map[objects->posmapx][objects->posmapy] == '1')
        objects->hit = 1;
    }
}

void	raycast(t_object_on_scene *objects, int x)
{
//calculate ray position and direction
      /*double cameraX*/objects->pos_camera_x = 2 * x / (double)objects->s_value_from_map.resolution_x - 1; //x-coordinate in camera space
      //                            -1                0                   0,001
      /*double rayDirX*/objects->rdx = objects->player_direction_x + objects->planeX * objects->pos_camera_x;
      /*double rayDirY*/objects->rdy = objects->player_direction_y + objects->planeY * objects->pos_camera_x;
      //which box of the map we're in
      /*int mapX*/objects->posmapx = (int)(objects->player_position_x);
      /*int mapY*/objects->posmapy = (int)(objects->player_position_y);

      //length of ray from current position to next x or y-side
      // double sideDistX;
      // double sideDistY;

       //length of ray from one x or y-side to next x or y-side
      /*double deltaDistX*/objects->del_dis_x = sqrt(1 + (objects->rdy * objects->rdy) / (objects->rdx * objects->rdx));
      /*double deltaDistY*/objects->del_dis_y = sqrt(1 + (objects->rdx * objects->rdx) / (objects->rdy * objects->rdy));
      //double perpWallDist;

      //what direction to step in x or y-direction (either +1 or -1)
      // int stepX;
      // int stepY;
      // int hit = 0; //was there a wall hit?
      objects->hit = 0;
	  calculate_side_dst(objects);
	  algoritm_dda(objects);
      // int side; //was a NS or a EW wall hit?
      //calculate step and initial sideDist
    //   if(objects->rdx < 0)
    //   {
    //     objects->step_x = -1;
    //     objects->side_dist_x = (objects->player_position_x - objects->posmapx) * objects->del_dis_x;
    //   }
    //   else
    //   {
    //     objects->step_x = 1;
    //     objects->side_dist_x = (objects->posmapx + 1.0 - objects->player_position_x) * objects->del_dis_x;
    //   }
    //   if(objects->rdy < 0)
    //   {
    //     objects->step_y = -1;
    //     objects->side_dist_y = (objects->player_position_y - objects->posmapy) * objects->del_dis_y;
    //   }
    //   else
    //   {
    //     objects->step_y = 1;
    //     objects->side_dist_y = (objects->posmapy + 1.0 - objects->player_position_y) * objects->del_dis_y;
    //   }
      //perform DDA
    //   while (objects->hit == 0)
    //   {
    //     //jump to next map square, OR in x-direction, OR in y-direction
    //     if (objects->side_dist_x < objects->side_dist_y)
    //     {
    //       objects->side_dist_x += objects->del_dis_x;
    //       objects->posmapx += objects->step_x;
    //       objects->side = 0; // попадание по Y
    //     }
    //     else
    //     {
    //       objects->side_dist_y += objects->del_dis_y;
    //       objects->posmapy += objects->step_y;
    //       objects->side = 1; // попадание по X
    //     }
    //     //Check if ray has hit a wall
    //     if (objects->map[objects->posmapx][objects->posmapy] == '1')
    //       objects->hit = 1;
    //   }
}
