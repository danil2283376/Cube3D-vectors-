/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 13:32:20 by scolen            #+#    #+#             */
/*   Updated: 2021/02/06 14:13:37 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"

void	draw_sprite(t_object_on_scene *objects)
{
	miscalculation_distance(objects);
	sorting_sprite(objects);
	for(int i = 0; i < objects->quantity_sprite; i++)
	{
		translate_sprite_pos(objects, i);
		calculate_height_sprite(objects);
		calculate_width_sprite(objects);
		draw_vertical_line(objects);
	}
}
