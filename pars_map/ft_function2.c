/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_function2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 19:33:05 by scolen            #+#    #+#             */
/*   Updated: 2021/02/06 22:22:52 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube_three_d.h"

int	return_value(char *line, int start, int count_space)
{
	if (((line[start] == 'R')
		|| (line[start] == 'N' && line[start + 1] == 'O')
		|| (line[start] == 'S' && line[start + 1] == 'O')
		|| (line[start] == 'W' && line[start + 1] == 'E')
		|| (line[start] == 'E' && line[start + 1] == 'A')
		|| (line[start] == 'S') || (line[start] == 'C')
		|| (line[start] == 'F')) && line[start] == '\0')
		return (0);
	if (count_space > 0 || (line[start] != '\0' && (line[start] != 'R'
		&& (line[start] != 'N' && line[start + 1] != 'O')
		&& (line[start] != 'S' && line[start + 1] != 'O')
		&& (line[start] != 'W' && line[start + 1] != 'E')
		&& (line[start] != 'E' && line[start + 1] != 'A')
		&& (line[start] != 'S') && (line[start] != 'C')
		&& (line[start] != 'F'))))
		return (1);
	return (0);
}
