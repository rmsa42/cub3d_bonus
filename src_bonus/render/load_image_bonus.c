/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_image_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:31:14 by rumachad          #+#    #+#             */
/*   Updated: 2024/06/21 14:39:56 by cacarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	pixel_get(t_image *img, int pixel_x, int pixel_y)
{
	int color;
	
	color =*(unsigned int*) (img->addr + (pixel_y * img->line_length + pixel_x * (img->bits_per_pixel / 8)));
	return (color);
}

void	pixel_put( t_image *img, int pixelX, int pixelY, int color)
{
	char	*dst;

	dst = img->addr + (pixelY * img->line_length + pixelX * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

t_image	image_buffer(t_mlx *mlx)
{
	t_image	img;

	img.img_ptr = mlx_new_image(mlx->lib, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img_ptr, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	return (img);
}
