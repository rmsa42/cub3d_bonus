/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:49:21 by rumachad          #+#    #+#             */
/*   Updated: 2024/05/31 12:13:26 by cacarval         ###   ########.fr       */
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

void draw_minimap(t_mlx *mlx) {
    int minimap_size = 200; // Size of the minimap in pixels
    int tile_size_x = minimap_size / mlx->map_width;
    int tile_size_y = minimap_size / mlx->map_height;
    int x, y;

    // Draw the map
    for (y = 0; y < mlx->map_height; y++) {
        for (x = 0; x < mlx->map_width; x++) {
            int color;
            if (mlx->map2[y][x] == '1')
                color = 0xFFFFFF; // White for walls
            else
                color = 0x000000; // Black for empty spaces

            int tile_x = x * tile_size_x;
            int tile_y = y * tile_size_y;

            for (int i = 0; i < tile_size_x; i++) {
                for (int j = 0; j < tile_size_y; j++) {
                    mlx_pixel_put(mlx->lib, mlx->window, tile_x + i, tile_y + j, color);
                }
            }
        }
    }

    // Draw the player
	print_vector(mlx->player.pos);
    int player_x = mlx->player.pos.x  * tile_size_x;
    int player_y = (mlx->player.pos.y - 6) * tile_size_y;
    int player_size = tile_size_x / 2;

    for (int i = -player_size; i < player_size; i++) {
        for (int j = -player_size; j < player_size; j++) {
            mlx_pixel_put(mlx->lib, mlx->window, player_x + i, player_y + j, 0xFF0000); // Red for player
        }
    }
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
	draw_minimap(mlx);
	mlx_destroy_image(mlx->lib, mlx->img.img_ptr);
	return (0);
}
