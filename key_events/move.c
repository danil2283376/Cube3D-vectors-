/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 21:33:34 by scolen            #+#    #+#             */
/*   Updated: 2021/02/06 22:22:34 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube_three_d.h"

void	move_up(t_object_on_scene *obj, float move_speed)
{
	if (obj->map[(int)(obj->player_position_x
				+ obj->player_direction_x * move_speed)]
					[(int)(obj->player_position_y)] == '0')
		obj->player_position_x += obj->player_direction_x * move_speed;
	if (obj->map[(int)(obj->player_position_x)][(int)(obj->player_position_y
				+ obj->player_direction_y * move_speed)] == '0')
		obj->player_position_y += obj->player_direction_y * move_speed;
}

void	move_down(t_object_on_scene *obj, float move_speed)
{
	if (obj->map[(int)(obj->player_position_x
				- obj->player_direction_x * move_speed)]
					[(int)(obj->player_position_y)] == '0')
		obj->player_position_x -= obj->player_direction_x * move_speed;
	if (obj->map[(int)(obj->player_position_x)]
			[(int)(obj->player_position_y
				- obj->player_direction_y * move_speed)] == '0')
		obj->player_position_y -= obj->player_direction_y * move_speed;
}

void	move_left(t_object_on_scene *obj, float move_speed)
{
	if (obj->map[(int)(obj->player_position_x)]
			[(int)(obj->player_position_y
				+ obj->player_direction_x * move_speed)] == '0')
		obj->player_position_y += obj->player_direction_x * move_speed;
	if (obj->map[(int)(obj->player_position_x
				- obj->player_direction_y * move_speed)]
					[(int)(obj->player_position_y)] == '0')
		obj->player_position_x -= obj->player_direction_y * move_speed;
}

void	move_right(t_object_on_scene *obj, float move_speed)
{
	if (obj->map[(int)(obj->player_position_x)]
			[(int)(obj->player_position_y
				- obj->player_direction_x * move_speed)] == '0')
		obj->player_position_y -= obj->player_direction_x * move_speed;
	if (obj->map[(int)(obj->player_position_x
				+ obj->player_direction_y * move_speed)]
					[(int)(obj->player_position_y)] == '0')
		obj->player_position_x += obj->player_direction_y * move_speed;
}
