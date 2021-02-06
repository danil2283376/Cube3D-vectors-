/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 13:32:20 by scolen            #+#    #+#             */
/*   Updated: 2021/02/06 22:21:54 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube_three_d.h"

void	draw_sprite(t_object_on_scene *objects)
{
	int i;

	i = 0;
	miscalculation_distance(objects);
	sorting_sprite(objects);
	while (i < objects->quantity_sprite)
	{
		translate_sprite_pos(objects, i);
		calculate_height_sprite(objects);
		calculate_width_sprite(objects);
		draw_vertical_line(objects);
		i++;
	}
}
