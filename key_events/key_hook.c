/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 21:34:18 by scolen            #+#    #+#             */
/*   Updated: 2021/02/06 00:31:25 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"

static void			event_move(int keycode, t_object_on_scene *obj)
{
	float move_speed; //the constant value is in squares/second

	move_speed = 0.1;
	if (keycode == 13) // up
		move_up(obj, move_speed);
	if (keycode == 1) // down
		move_down(obj, move_speed);
	if (keycode == 0) // влево
	move_left(obj, move_speed);
	if (keycode == 2) // вправо
		move_right(obj, move_speed);
}

static void		event_rotation(int keycode, t_object_on_scene *obj)
{
	float rotation_speed;

	rotation_speed = 0.1;
	if (keycode == 124)
		rotation_right(obj, rotation_speed);
	if (keycode == 123)
		rotation_left(obj, rotation_speed);
}

int				key_hook(int keycode, t_object_on_scene *obj)
{
	if (keycode == 53)
	{
		system("killall afplay");
		exit(1);
	}
	event_move(keycode, obj);
	event_rotation(keycode, obj);
	mlx_destroy_image(obj->mlx, obj->window.img);
	obj->window.img = mlx_new_image(obj->mlx, obj->s_value_from_map.resolution_x, obj->s_value_from_map.resolution_y);
		obj->window.addr = mlx_get_data_addr(obj->window.img, &obj->window.bits_per_pixel,
			&obj->window.line_length, &obj->window.endian);
	rebuild_scene(obj);
	mlx_put_image_to_window(obj->mlx, obj->win, obj->window.img, 0, 0);
	return (1);
}
