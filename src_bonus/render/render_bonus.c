/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:49:21 by rumachad          #+#    #+#             */
/*   Updated: 2024/05/31 15:33:46 by cacarval         ###   ########.fr       */
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

void put_tiles(t_mlx *mlx,int tile_size_x, int tile_size_y)
{
    int x;
    int y;
    int i;
    int j;

    i = -1;
    j = -1;
    x = -1;
    y = -1;
    while (++y < mlx->map_height) 
    {
        x = -1;
        while (++x < mlx->map_width) 
        {
            int color;
            if (mlx->map.game_map[y][x] == '0')
                color = 0x000000;
            else if(mlx->map.game_map[y][x] == 'D' || mlx->map.game_map[y][x] == 'd')
                color = 0x0050FF;
            else
                color = 0xFFFFFF;
            int tile_x = x * tile_size_x;
            int tile_y = y * tile_size_y;
            i = -1;
            while (++i < tile_size_x) 
            {
                j = -1;
                while (++j < tile_size_y) 
                    mlx_pixel_put(mlx->lib, mlx->window, tile_x + i, tile_y + j, color);
            }
        }
    }
}

void draw_minimap(t_mlx *mlx) 
{
    int minimap_size = 200;
    int tile_size_x = minimap_size / mlx->map_width;
    int tile_size_y = minimap_size / mlx->map_height;

    put_tiles(mlx, tile_size_x, tile_size_y);
    int player_x = mlx->player.pos.x * tile_size_x;
    int player_y = mlx->player.pos.y * tile_size_y;
    int player_size = tile_size_x / 2;
    int i = -player_size;
    while (i < player_size) {
        int j = -player_size;
        while (j < player_size) {
            mlx_pixel_put(mlx->lib, mlx->window, player_x + i, player_y + j, 0xFF0000);
            j++;
        }
        i++;
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
