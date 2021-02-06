/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_three_d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 21:30:26 by scolen            #+#    #+#             */
/*   Updated: 2021/02/06 23:10:50 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_three_d.h"

#define TEXHEIGHT 64

void	calculate_dst(t_object_on_scene *objects, int x)
{
	objects->perp_dist[x] = objects->per_wall_dst;
	objects->line_ray = (int)(objects->s_value_from_map.resolution_y
				/ objects->per_wall_dst);
	calculate_start_end_wall(objects);
	objects->steps_texture = 1.0 * TEXHEIGHT / objects->line_ray;
	objects->texture_pos = (objects->start_wall
			- objects->s_value_from_map.resolution_y /
			2 + objects->line_ray / 2) * objects->steps_texture;
}

int		rebuild_scene(t_object_on_scene *objects)
{
	int x;

	x = 0;
	while (x < objects->s_value_from_map.resolution_x)
	{
		raycast(objects, x);
		if (objects->side == 0)
			objects->per_wall_dst = (objects->posmapx
					- objects->player_position_x +
					(1 - objects->step_x) / 2) / objects->rdx;
		else
			objects->per_wall_dst = (objects->posmapy
					- objects->player_position_y +
					(1 - objects->step_y) / 2) / objects->rdy;
		calculate_dst(objects, x);
		paint_wall(objects, x);
		x++;
	}
	draw_sprite(objects);
	return (1);
}

int		close_window(t_object_on_scene *objects)
{
	mlx_destroy_window(objects->mlx, objects->win);
	exit(1);
	return (1);
}

void	init_window(t_object_on_scene *objects)
{
	objects->mlx = mlx_init();
	objects->win = mlx_new_window(objects->mlx,
			objects->s_value_from_map.resolution_x,
			objects->s_value_from_map.resolution_y, "Cube3D");
	take_position_player(objects);
	cardinal_points(objects);
	quantity_sprite1(objects);
	objects->speed = 5;
	objects->window.img = mlx_new_image(objects->mlx,
			objects->s_value_from_map.resolution_x,
			objects->s_value_from_map.resolution_y);
	objects->window.addr = mlx_get_data_addr(objects->window.img,
			&objects->window.bits_per_pixel,
			&objects->window.line_length, &objects->window.endian);
	filling_struct_texture(objects);
}

int		main(int argc, char **argv)
{
	t_object_on_scene	objects;
	int					fd;

	validate_arguments(argv[1], &objects, argc, argv);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		threatment_error(1, "Not exist file!", &objects);
	manage_function(fd, &objects.s_value_from_map, &objects);
	validate_map1(&objects, fd, argv[1]);
	objects.perp_dist = malloc(sizeof(float)
			* objects.s_value_from_map.resolution_x);
	init_window(&objects);
	if (argc == 3)
		is_screenshot(&objects);
	else
	{
		system("afplay DJ_Vasya_Deep_House.mp3 & ");
		rebuild_scene(&objects);
		mlx_put_image_to_window(objects.mlx,
				objects.win, objects.window.img, 0, 0);
		mlx_hook(objects.win, 2, 1L << 0, key_hook, &objects);
		mlx_hook(objects.win, 17, 1L << 0, close_window, &objects);
		mlx_loop(objects.mlx);
	}
}
