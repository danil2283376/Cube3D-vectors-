/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 18:58:26 by scolen            #+#    #+#             */
/*   Updated: 2021/02/06 22:23:29 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube_three_d.h"

#define TEXWIDTH 64
#define TEXHEIGHT 64

void	draw_n_or_s(t_object_on_scene *objects, int x, int y)
{
	unsigned int color;

	color = 0;
	if (objects->step_x > 0)
	{
		color = take_pixel_from_texture(&objects->texture_north,
			objects->texture_x, objects->texture_y);
		my_mlx_pixel_put(&objects->window, x, y, color);
	}
	else if (objects->step_x < 0)
	{
		color = take_pixel_from_texture(&objects->texture_south,
			objects->texture_x, objects->texture_y);
		my_mlx_pixel_put(&objects->window, x, y, color);
	}
}

void	draw_w_or_e(t_object_on_scene *objects, int x, int y)
{
	unsigned int color;

	color = 0;
	if (objects->step_y > 0)
	{
		color = take_pixel_from_texture(&objects->texture_west,
			objects->texture_x, objects->texture_y);
		my_mlx_pixel_put(&objects->window, x, y, color);
	}
	else if (objects->step_y < 0)
	{
		color = take_pixel_from_texture(&objects->texture_east,
			objects->texture_x, objects->texture_y);
		my_mlx_pixel_put(&objects->window, x, y, color);
	}
}

void	calculate_start_end_wall(t_object_on_scene *objects)
{
	int h;

	h = objects->s_value_from_map.resolution_y;
	objects->start_wall = -objects->line_ray / 2 + h / 2;
	if (objects->start_wall < 0)
		objects->start_wall = 0;
	objects->end_wall = objects->line_ray / 2 + h / 2;
	if (objects->end_wall >= h)
		objects->end_wall = h - 1;
	if (objects->side == 0)
		objects->hit_wall = objects->player_position_y
			+ objects->per_wall_dst * objects->rdy;
	else
		objects->hit_wall = objects->player_position_x
			+ objects->per_wall_dst * objects->rdx;
	objects->hit_wall -= floor((objects->hit_wall));
}

void	paint_texture(t_object_on_scene *objects, int x, int y)
{
	while (y < objects->s_value_from_map.resolution_y)
	{
		if (y < objects->start_wall)
			my_mlx_pixel_put(&objects->window, x, y,
				threatment_color(objects->s_value_from_map.ceilling_color_r,
					objects->s_value_from_map.ceilling_color_g,
						objects->s_value_from_map.ceilling_color_b));
		if (y > objects->start_wall && y < objects->end_wall)
		{
			objects->texture_y = (int)objects->texture_pos & (TEXHEIGHT - 1);
			objects->texture_pos += objects->steps_texture;
			if (objects->side == 0)
				draw_n_or_s(objects, x, y);
			else if (objects->side == 1)
				draw_w_or_e(objects, x, y);
		}
		if (y > objects->end_wall)
			my_mlx_pixel_put(&objects->window, x, y,
				threatment_color(objects->s_value_from_map.floor_color_r,
					objects->s_value_from_map.floor_color_g,
						objects->s_value_from_map.floor_color_b));
		y++;
	}
}

void	paint_wall(t_object_on_scene *objects, int x)
{
	int y;

	y = 0;
	objects->texture_x = (int)(objects->hit_wall * (double)(TEXWIDTH));
	if (objects->side == 0 && objects->rdx > 0)
		objects->texture_x = TEXWIDTH - objects->texture_x - 1;
	if (objects->side == 1 && objects->rdy < 0)
		objects->texture_x = TEXWIDTH - objects->texture_x - 1;
	objects->steps_texture = 1.0 * TEXHEIGHT / objects->line_ray;
	objects->texture_pos = (objects->start_wall
		- objects->s_value_from_map.resolution_y
			/ 2 + objects->line_ray / 2) * objects->steps_texture;
	paint_texture(objects, x, y);
}
