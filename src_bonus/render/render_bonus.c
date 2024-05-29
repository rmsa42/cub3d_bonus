/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:49:21 by rumachad          #+#    #+#             */
/*   Updated: 2024/05/29 11:37:58 by cacarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_image	new_image(t_mlx *mlx)
{
	t_image	img;

	img.img_ptr = mlx_new_image(mlx->lib, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img_ptr, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	return (img);
}

int	render(t_mlx *mlx)
{
	int i = -1;
	update(mlx);
	mlx->img = new_image(mlx);
	while (++i < 4)
	{
		mlx->sprite[i].img.addr = mlx_get_data_addr(mlx->sprite[i].img.img_ptr,
			&mlx->sprite[i].img.bits_per_pixel, &mlx->sprite[i].img.line_length, &mlx->sprite[i].img.endian);
	}
	i = 5;
	while (++i < 13)
	{
		mlx->sprite[i].img.addr = mlx_get_data_addr(mlx->sprite[i].img.img_ptr,
				&mlx->sprite[i].img.bits_per_pixel, &mlx->sprite[i].img.line_length, &mlx->sprite[i].img.endian);
	}
	/* mlx->sprite[7].img.addr = mlx_get_data_addr(mlx->sprite[7].img.img_ptr,
			&mlx->sprite[7].img.bits_per_pixel, &mlx->sprite[7].img.line_length, &mlx->sprite[7].img.endian); */
	ft_grua(mlx);
	mlx_destroy_image(mlx->lib, mlx->img.img_ptr);
	return (0);
}
