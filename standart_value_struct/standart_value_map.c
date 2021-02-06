/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   standart_value_map.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 11:55:13 by scolen            #+#    #+#             */
/*   Updated: 2021/02/06 22:23:51 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube_three_d.h"

void	malloc_array_sprite(t_object_on_scene *objects)
{
	objects->pos_sprite_x = malloc(sizeof(float) * objects->quantity_sprite);
	objects->pos_sprite_y = malloc(sizeof(float) * objects->quantity_sprite);
	objects->struct_array =
		malloc(sizeof(t_info_image) * objects->quantity_sprite);
	if (objects->pos_sprite_x == NULL || objects->pos_sprite_y == NULL ||
		objects->struct_array == NULL)
		threatment_error(1, "error map!", objects);
}

void	convert_xpm_to_image(t_object_on_scene *objects,
	t_info_image *texture, char *path)
{
	char *relative_path;
	void *img;

	relative_path = path;
	img = mlx_xpm_file_to_image(objects->mlx,
		relative_path, &texture->width_x, &texture->height_y);
	if (img != NULL)
	{
		texture->addr = mlx_get_data_addr(img, &texture->bits_per_pixel,
			&texture->line_length, &texture->endian);
	}
	else
		threatment_error(1, "Not valide path to texture", objects);
}

void	filling_struct_texture(t_object_on_scene *objects)
{
	convert_xpm_to_image(objects, &objects->texture_north,
		objects->s_value_from_map.north_texture);
	convert_xpm_to_image(objects, &objects->texture_east,
		objects->s_value_from_map.east_texture);
	convert_xpm_to_image(objects, &objects->texture_south,
		objects->s_value_from_map.south_texture);
	convert_xpm_to_image(objects, &objects->texture_west,
		objects->s_value_from_map.west_texture);
	convert_xpm_to_image(objects, &objects->texture_sprite,
		objects->s_value_from_map.sprite_texture);
}

void	standart_value_map(t_object_on_scene *objects)
{
	objects->s_value_from_map.resolution_x = -1;
	objects->s_value_from_map.resolution_y = -1;
	objects->s_value_from_map.north_texture = NULL;
	objects->s_value_from_map.south_texture = NULL;
	objects->s_value_from_map.west_texture = NULL;
	objects->s_value_from_map.east_texture = NULL;
	objects->s_value_from_map.sprite_texture = NULL;
	objects->s_value_from_map.ceilling_color_r = -1;
	objects->s_value_from_map.ceilling_color_g = -1;
	objects->s_value_from_map.ceilling_color_b = -1;
	objects->s_value_from_map.floor_color_r = -1;
	objects->s_value_from_map.floor_color_g = -1;
	objects->s_value_from_map.floor_color_b = -1;
	objects->s_value_from_map.valide_map = 1;
	objects->s_value_from_map.quantity_string = 0;
	objects->s_value_from_map.quantity_player = 0;
	objects->s_value_from_map.quantity_string_map = 0;
	objects->s_value_from_map.quantity_string_before_map = 0;
	objects->s_value_from_map.meet_map = 0;
}
