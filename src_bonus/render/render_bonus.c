/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:49:21 by rumachad          #+#    #+#             */
/*   Updated: 2024/06/03 15:11:08 by cacarval         ###   ########.fr       */
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

void minimap_tiles(t_mlx *mlx,int tile_size_x, int tile_size_y)
{
    int x;
    int y;
    int i;
    int j;
    static int flag;
    i = -1;
    j = -1;
    x = -1;
    y = -1;
    while (++y < mlx->map_height) 
    {
        x = -1;
        flag = 0;
        while (++x < mlx->map_width) 
        {
            int color;
            if (mlx->map.game_map[y][x] == '0' && flag == 0)
            {
                // printf("x:%i,y:%i\n", x, y );
                color = 0x000000;
            }
            else if(mlx->map.game_map[y][x] == 'D' || mlx->map.game_map[y][x] == 'd')
                color = 0x0050FF;
            else
                color = 0xFFFFFF;
            if (mlx->map.game_map[y][x] == '\n')
                flag = 1;
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
    // int tile_size_x = minimap_size / mlx->map_width;
    int tile_size = minimap_size / mlx->map_height;

    minimap_tiles(mlx, tile_size, tile_size);
    int sprite_x = mlx->spr_pos.x * tile_size;
    int sprite_y =mlx->spr_pos.y * tile_size;
    int player_x = mlx->player.pos.x * tile_size;
    int player_y = mlx->player.pos.y * tile_size;
    int player_size = tile_size / 2;
    int i = -player_size;
    while (i < player_size) {
        int j = -player_size;
        while (j < player_size) {
            mlx_pixel_put(mlx->lib, mlx->window, sprite_x + i, sprite_y + j, 0xFF00FF);
            mlx_pixel_put(mlx->lib, mlx->window, player_x + i, player_y + j, 0x00FF00);
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
	while (++i < 14)
	{
		mlx->sprite[i].img.addr = mlx_get_data_addr(mlx->sprite[i].img.img_ptr,
				&mlx->sprite[i].img.bits_per_pixel, &mlx->sprite[i].img.line_length, &mlx->sprite[i].img.endian);
	}
	ft_grua(mlx);
	draw_minimap(mlx);
	mlx_destroy_image(mlx->lib, mlx->img.img_ptr);
	return (0);
}
