/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_pixel_from_texture.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scolen <scolen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 11:47:46 by scolen            #+#    #+#             */
/*   Updated: 2021/02/06 14:46:21 by scolen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"

unsigned int            take_pixel_from_texture(t_info_image *img, int x, int y)
{
    unsigned int color;
    char    *dst;
    dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    color = *(unsigned int *)dst;
    return (color);
}
