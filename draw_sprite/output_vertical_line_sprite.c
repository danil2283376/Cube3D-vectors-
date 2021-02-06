/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_vertical_line_sprite.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 21:27:26 by scolen            #+#    #+#             */
/*   Updated: 2021/02/06 14:25:30 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3D.h"

#define texWidth 64
#define texHeight 64

static	void	vertical_line(t_object_on_scene *objects, int x)
{
	int d;
	int y;

	d = 0;
	y = objects->start_sprite_y;
	while (y < objects->end_sprite_y)
	{
		d = (y) * 256 - objects->s_value_from_map.resolution_y * 128 + objects->sprite_height * 128;
		objects->texture_sprite_y = ((d * texHeight) / objects->sprite_height) / 256;
		objects->color_pixel_sprite = take_pixel_from_texture(&objects->texture_sprite,
		objects->texture_sprite_x, objects->texture_sprite_y);
		if (objects->color_pixel_sprite > 0)
			my_mlx_pixel_put(&objects->window, x, y, objects->color_pixel_sprite);
		y++;
	}
}

void			draw_vertical_line(t_object_on_scene *objects)
{
	int d;
	int x;

	d = 0;
	x = objects->start_sprite_x;
	while (x < objects->end_sprite_x)
	{
		objects->texture_sprite_x = (int)(256 * (x - (-objects->width_sprite /
		2 + objects->screen_pos_x)) * texWidth / objects->width_sprite) / 256;

		if (objects->transform_pos_y > 0 && x > 0 && x < objects->s_value_from_map.resolution_x
			&& objects->transform_pos_y < objects->perp_dist[x])
			vertical_line(objects, x);
		x++;
	}
}
