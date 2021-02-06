/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   this_screenshot.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 22:17:53 by scolen            #+#    #+#             */
/*   Updated: 2021/02/06 22:23:43 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube_three_d.h"

void	is_screenshot(t_object_on_scene *objects)
{
	rebuild_scene(objects);
	screenshot(objects);
}
