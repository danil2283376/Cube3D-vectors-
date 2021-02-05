/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_vertical_line_sprite.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 21:27:26 by scolen            #+#    #+#             */
/*   Updated: 2021/02/05 21:30:57 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

#define texWidth 64
#define texHeight 64

void	draw_vertical_line(t_object_on_scene *objects)
{
	int d;

	d = 0;
	for(int stripe = objects->start_sprite_x; stripe < objects->end_sprite_x; stripe++)
	{
		/*int texX*/objects->texture_sprite_x = (int)(256 * (stripe - (-objects->width_sprite /
		2 + objects->screen_pos_x)) * texWidth / objects->width_sprite) / 256;

		if (objects->transform_pos_y > 0 && stripe > 0 && stripe < objects->s_value_from_map.resolution_x
			&& objects->transform_pos_y < objects->perp_dist[stripe])
		for (int y = objects->start_sprite_y; y < objects->end_sprite_y; y++) //for every pixel of the current stripe
		{
			// printf("1\n");
			d = (y) * 256 - objects->s_value_from_map.resolution_y * 128 + objects->sprite_height * 128; //256 and 128 factors to avoid floats
			/*int texY*/ objects->texture_sprite_y = ((d * texHeight) / objects->sprite_height) / 256;
			/*int color*/objects->color_pixel_sprite = take_pixel_from_texture(&objects->texture_sprite,
			objects->texture_sprite_x, objects->texture_sprite_y);
			// write(1, "1", 1);
			if (objects->color_pixel_sprite > 0)
			my_mlx_pixel_put(&objects->window, stripe, y, objects->color_pixel_sprite); //paint pixel if it isn't black, black is the invisible color
		}
	}
}
