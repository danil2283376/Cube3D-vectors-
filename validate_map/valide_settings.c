/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valide_settings.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 12:47:04 by scolen            #+#    #+#             */
/*   Updated: 2021/02/03 21:08:37 by scolen           ###   ########.fr       */
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
	int i;
	int j;

	i = 0;
	j = 0;
	while (objects->map[i] != NULL)
	{
		while (objects->map[i][j] != '\0')
		{
			if (objects->map[i][j] == 'N' || objects->map[i][j] == 'W' ||
				objects->map[i][j] == 'S' || objects->map[i][j] == 'E')
					objects->s_value_from_map.quantity_player++;
			j++;
		}
		i++;
		j = 0;
	}
	if (objects->s_value_from_map.quantity_player != 1)
		threatment_error(1, "Error map!", objects);
	check_valide_map(objects);
	// printf("objects->s_value_from_map.valide_map: %d\n", objects->s_value_from_map.valide_map);
	if (objects->s_value_from_map.valide_map == -1)
		threatment_error(1, "Incorrect map3!", objects);
}

void	normalize_resolution(t_object_on_scene *objects)
{
	int size_x;
	int size_y;

	mlx_get_screen_size(objects->mlx, &size_x, &size_y);
	if (objects->s_value_from_map.resolution_x > size_x)
		objects->s_value_from_map.resolution_x = size_x;
	if (objects->s_value_from_map.resolution_y > size_y)
		objects->s_value_from_map.resolution_y = size_y;
}

void	check_string_after_map(t_object_on_scene *objects, int fd, char *name_file)
{
	int i;
	int fd1;
	char *line;

	i = 0;
	close(fd);
	fd1 = open(name_file, O_RDONLY);
	while (get_next_line(fd1, &line))
	{
		if (i != objects->s_value_from_map.quantity_string_map)
			free(line);
		if (i == objects->s_value_from_map.quantity_string_map - 1)
			break ;
		// if (i == 20)
		// 	break ;
		i++;
	}
	i = 0;
	while (objects->map[i])
	{
		objects->s_value_from_map.quantity_string_before_map++;
		i++;
	}
	printf("objects->s_value_from_map.quantity_string_before_map: %d\n", objects->s_value_from_map.quantity_string_before_map);
	printf("i = %d, objects->s_value_from_map.quantity_string_map: %d\n", i, objects->s_value_from_map.quantity_string_map);
	// if (i == objects->s_value_from_map.quantity_string_map + 1)
	// {
		// write(1, "111", 3);
		// printf("str = %s\n", line);
		i = 0;
		// while ((line[i] == ' ' || line[i] == '\t') && line[i] != '\0')
		// 	i++;
			// printf("aaa = %s\n|", line);
		// if (line == '\0')
		// 	threatment_error(1, "Error map!1", objects);
		// while (line[i] == ' ' || line[i] == '\t' || line[i] == '1' ||
		// 	line[i] == '0' || line[i] == 'N' || line[i] == 'S' ||
		// 	line[i] == 'W' || line[i] == 'E' || line[i] == '2')
		// if (line[0] != '\0')
		// 	i++;
		// printf("");
		// write(1, "2\n", 2);
		// while (line[i] == ' ' || line[i] == '\t')
		// 	i++;
		// if (line[0] != '\0')
		if (objects->s_value_from_map.quantity_string_map > objects->s_value_from_map.quantity_string_before_map)
			threatment_error(1, "Error map!2", objects);
		// write(1, "1\n", 2);
		// if ((line[i] != ' ' || line[i] != '\t') && line[i] != '\0')
		// 	threatment_error(1, "Error map!2", objects);
	// }
	// write(1, "1", 1);
	// printf("str = %s\n", objects->map[objects->s_value_from_map.quantity_string_map - 1]);
}

void	validate_map1(t_object_on_scene *objects, int fd, char *name_file)
{
	(void)fd;
	(void)name_file;
	check_string_after_map(objects, fd, name_file); // добавить валидацию, на то что после карты есть символы
	normalize_resolution(objects);
	validate_matrix_map(objects); // валидация матрицы
	printf("\n%d\n\n\n", 1);
	if (objects->s_value_from_map.resolution_x <= 0 ||
		objects->s_value_from_map.resolution_y <= 0)
		threatment_error(1, "Incorrect map1!", objects);
	if (objects->s_value_from_map.north_texture == NULL ||
		objects->s_value_from_map.south_texture == NULL ||
		objects->s_value_from_map.west_texture == NULL ||
		objects->s_value_from_map.east_texture == NULL ||
		objects->s_value_from_map.sprite_texture == NULL)
		threatment_error(1, "Incorrect map2!", objects);
	if (objects->s_value_from_map.ceilling_color_r == -1 || objects->s_value_from_map.ceilling_color_r > 255 ||
		objects->s_value_from_map.ceilling_color_g == -1 || objects->s_value_from_map.ceilling_color_g > 255 ||
		objects->s_value_from_map.ceilling_color_b == -1 || objects->s_value_from_map.ceilling_color_b > 255 ||
		objects->s_value_from_map.floor_color_r == -1 || objects->s_value_from_map.floor_color_r > 255 ||
		objects->s_value_from_map.floor_color_g == -1 || objects->s_value_from_map.floor_color_g > 255 ||
		objects->s_value_from_map.floor_color_b == -1 || objects->s_value_from_map.floor_color_b > 255)
		threatment_error(1, "Incorrect color!", objects);
	// if (objects->s_value_from_map.valide_map == -1)
	// 	threatment_error(1, "Not validate map!", objects);
}
