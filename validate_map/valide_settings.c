/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valide_settings.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 12:47:04 by scolen            #+#    #+#             */
/*   Updated: 2021/01/31 18:23:34 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"

void	threatment_error(int fd, char *error, t_object_on_scene *objects)
{
	(void)objects;
	ft_putendl_fd(error, fd);
	// mlx_destroy_image(objects->mlx, objects->window.img);
	// mlx_destroy_window(objects->mlx, objects->win);
	exit(1);
}

void	validate_matrix_map(t_object_on_scene *objects)
{
	check_valide_map(objects);
	if (objects->s_value_from_map.valide_map == -1)
		threatment_error(1, "Incorrect map!", objects);
}

void	validate_map1(t_object_on_scene *objects)
{
	if (objects->s_value_from_map.resolution_x <= 0 ||
		objects->s_value_from_map.resolution_y <= 0)
		threatment_error(1, "Incorrect resolution!", objects);

	if (objects->s_value_from_map.north_texture == NULL ||
		objects->s_value_from_map.south_texture == NULL ||
		objects->s_value_from_map.west_texture == NULL ||
		objects->s_value_from_map.east_texture == NULL ||
		objects->s_value_from_map.sprite_texture == NULL)
		threatment_error(1, "Incorrect path!", objects);

	if (objects->s_value_from_map.ceilling_color_r == -1 ||
		objects->s_value_from_map.ceilling_color_g == -1 ||
		objects->s_value_from_map.ceilling_color_b == -1 ||
		objects->s_value_from_map.floor_color_r == -1 ||
		objects->s_value_from_map.floor_color_g == -1 ||
		objects->s_value_from_map.floor_color_b == -1)
		threatment_error(1, "Incorrect color!", objects);
	// validate_matrix_map(objects); // валидация матрицы
}
