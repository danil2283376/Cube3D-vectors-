/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cardinal_points.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 12:04:18 by scolen            #+#    #+#             */
/*   Updated: 2021/02/06 22:37:15 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube_three_d.h"

void	cardinal_points(t_object_on_scene *objects)
{
	if (objects->cardinal_point == 'N')
	{
		objects->player_direction_x = -1;
		objects->plane_y = 0.66;
	}
	if (objects->cardinal_point == 'S')
	{
		objects->player_direction_x = 1;
		objects->plane_y = -0.66;
	}
	if (objects->cardinal_point == 'W')
	{
		objects->player_direction_y = -1;
		objects->plane_x = -0.66;
	}
	if (objects->cardinal_point == 'E')
	{
		objects->player_direction_y = 1;
		objects->plane_x = 0.66;
	}
}
