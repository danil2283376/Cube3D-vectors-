/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_function1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 12:44:31 by scolen            #+#    #+#             */
/*   Updated: 2021/02/06 22:22:47 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube_three_d.h"

void	standart_value_struct(t_value_from_map *value_map)
{
	value_map->resolution_x = -1;
	value_map->resolution_y = -1;
	value_map->north_texture = NULL;
	value_map->south_texture = NULL;
	value_map->west_texture = NULL;
	value_map->east_texture = NULL;
	value_map->sprite_texture = NULL;
	value_map->floor_color_r = -1;
	value_map->floor_color_g = -1;
	value_map->floor_color_b = -1;
	value_map->ceilling_color_r = -1;
	value_map->ceilling_color_g = -1;
	value_map->ceilling_color_b = -1;
}

int		value_from_maps_not_null(t_value_from_map *value_map)
{
	if ((value_map->resolution_x >= 1 &&
		value_map->resolution_y >= 1) &&
		(value_map->north_texture != NULL &&
		value_map->south_texture != NULL &&
		value_map->west_texture != NULL &&
		value_map->east_texture != NULL &&
		value_map->sprite_texture != NULL) &&
		(value_map->floor_color_r >= 0 &&
		value_map->floor_color_g >= 0 &&
		value_map->floor_color_b >= 0) &&
		(value_map->ceilling_color_r >= 0 &&
		value_map->ceilling_color_g >= 0 &&
		value_map->ceilling_color_b >= 0))
		return (1);
	return (0);
}
