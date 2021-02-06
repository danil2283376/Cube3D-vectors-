/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 00:18:29 by scolen            #+#    #+#             */
/*   Updated: 2021/02/06 22:36:57 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube_three_d.h"

void	rotation_left(t_object_on_scene *obj, float speed_rotation)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = obj->player_direction_x;
	obj->player_direction_x = obj->player_direction_x *
		cos(speed_rotation) - obj->player_direction_y * sin(speed_rotation);
	obj->player_direction_y = old_dir_x * sin(speed_rotation)
		+ obj->player_direction_y * cos(speed_rotation);
	old_plane_x = obj->plane_x;
	obj->plane_x = obj->plane_x *
		cos(speed_rotation) - obj->plane_y * sin(speed_rotation);
	obj->plane_y = old_plane_x *
		sin(speed_rotation) + obj->plane_y * cos(speed_rotation);
}

void	rotation_right(t_object_on_scene *obj, float speed_rotation)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = obj->player_direction_x;
	obj->player_direction_x = obj->player_direction_x
		* cos(-speed_rotation) - obj->player_direction_y * sin(-speed_rotation);
	obj->player_direction_y = old_dir_x * sin(-speed_rotation)
		+ obj->player_direction_y * cos(-speed_rotation);
	old_plane_x = obj->plane_x;
	obj->plane_x = obj->plane_x * cos(-speed_rotation)
		- obj->plane_y * sin(-speed_rotation);
	obj->plane_y = old_plane_x * sin(-speed_rotation)
		+ obj->plane_y * cos(-speed_rotation);
}
