/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:49:21 by rumachad          #+#    #+#             */
/*   Updated: 2024/06/07 15:35:56 by cacarval         ###   ########.fr       */
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

void minimap_tiles(t_mlx *mlx,int tile_size)
{
	int x;
	int y;
	int i;
	int j;
	int flag;
	i = -1;
	j = -1;
	y = -1;
	while (++y < mlx->map_height) 
	{
		x = -1;
		flag = 0;
		while (++x < (int)ft_strlen(mlx->map.game_map[y])) 
		{
			int color;
			if (mlx->map.game_map[y][x] == '0' && flag == 0)
				color = 0x9c9c9c;
			else if(mlx->map.game_map[y][x] == 'D' || mlx->map.game_map[y][x] == 'd')
				color = 0x0050FF;
			else if (mlx->map.game_map[y][x] == 'X')
				color = 0xFFFFFF;
			else
				color = 0x000000;
			if (mlx->map.game_map[y][x] == '\n')
				flag = 1;
			int tile_x = x * tile_size;
			int tile_y = y * tile_size;
			i = -1;
			while (++i < tile_size) 
			{
				j = -1;
				while (++j < tile_size)
					pixel_put(&mlx->img, tile_x + i, tile_y + j, color);
			}
		}
	}
}

void draw_minimap(t_mlx *mlx) 
{
	int minimap_size = 200;
	int tile_size = minimap_size / 36;
	int k;
	t_objs	*objs;
	int ball_x;
	int ball_y;
	minimap_tiles(mlx, tile_size);
	if (mlx->player.shoot == true)
	{
		ball_x = mlx->ball_pos.x * tile_size;
		ball_y = mlx->ball_pos.y * tile_size;
	}
	int player_x = mlx->player.pos.x * tile_size;
	int player_y = mlx->player.pos.y * tile_size;
	int player_size = tile_size / 2;
	int i = -player_size;
	while (i < player_size) 
	{
		int j = -player_size;
		while (j < player_size) 
		{
			k = -1;
			objs = mlx->objs;
			while (objs != NULL)
			{
				int sprite_x = objs->pos.x * tile_size;
				int sprite_y = objs->pos.y * tile_size;
				pixel_put(&mlx->img, sprite_x + i, sprite_y + j, 0xFF0000);
				objs = objs->next;
			}
			if (mlx->player.shoot == true)
				pixel_put(&mlx->img, ball_x + i, ball_y + j, 0x0000FF);
			pixel_put(&mlx->img, player_x + i, player_y + j, 0x00FF00);
			j++;
		}
		i++;
	}
}

int	render(t_mlx *mlx)
{
	struct timespec current_time;

	if (mlx->last_time.tv_sec == 0 && mlx->last_time.tv_nsec == 0)
		update_time(&mlx->last_time);
	update_time(&current_time);
	mlx->elapsed_time = time_passed(&mlx->last_time, &current_time);
	update_player(mlx, &mlx->player, &mlx->map);
	update_sprites(&mlx->player, mlx->objs);
	mlx->img = new_image(mlx);
	ft_grua(mlx);
	enemy_ray(mlx);
	draw_minimap(mlx);
	mlx_destroy_image(mlx->lib, mlx->img.img_ptr);
	return (0);
}
