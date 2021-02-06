/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_position_player.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 12:00:58 by scolen            #+#    #+#             */
/*   Updated: 2021/02/06 22:23:54 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube_three_d.h"

void	take_position_player(t_object_on_scene *objects)
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
				objects->map[i][j] == 'E' || objects->map[i][j] == 'S')
			{
				objects->player_position_x = i + 0.1;
				objects->player_position_y = j + 0.1;
				objects->cardinal_point = objects->map[i][j];
			}
			j++;
		}
		i++;
		j = 0;
	}
	objects->map[(int)(objects->player_position_x)]
		[(int)(objects->player_position_y)] = '0';
}
