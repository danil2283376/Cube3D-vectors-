/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 11:50:48 by scolen            #+#    #+#             */
/*   Updated: 2021/02/06 14:47:35 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"

static void	filling_file_screenshot(int fd, t_object_on_scene *obj)
{
	int	i;
	int	j;
	int	color;

	i = obj->s_value_from_map.resolution_y;
	while (--i >= 0)
	{
		j = -1;
		while (++j < obj->s_value_from_map.resolution_x)
		{
			color = *(int*)(obj->window.addr + (i * obj->window.line_length
					+ j * (obj->window.bits_per_pixel / 8)));
			write(fd, &color, 4);
		}
	}
}

void  screenshot(t_object_on_scene *objects)
{
  int fd;
  int size_screen = objects->s_value_from_map.resolution_x * objects->s_value_from_map.resolution_y * 4 + 54;
  int zero = 0;
  int pos_pixel_data = 54;
  short plane = 1;
  int size = objects->s_value_from_map.resolution_x * objects->s_value_from_map.resolution_y;

  fd = open("screen.bmp", O_CREAT | O_RDWR, 0666);
  if (fd < 0) // вывод ошибки
    exit(1);
  write(fd, "BM", 2);
  write(fd, &size_screen, 4);
  write(fd, &zero, 4);
  write(fd, &pos_pixel_data, 4);
  pos_pixel_data = 40;
  write(fd, &pos_pixel_data, 4);
  write(fd, &objects->s_value_from_map.resolution_x, 4);
  write(fd, &objects->s_value_from_map.resolution_y, 4);
  write(fd, &plane, 2);
  plane = 32;
  write(fd, &plane, 2);
  write(fd, &zero, 4);
  write(fd, &size, 4);
  size_screen = 1000;
  write(fd, &size_screen, 4);
  write(fd, &size_screen, 4);
  write(fd, &zero, 4);
  write(fd, &zero, 4);
  // write(fd, &objects->window, 4);
  filling_file_screenshot(fd, objects);
}
