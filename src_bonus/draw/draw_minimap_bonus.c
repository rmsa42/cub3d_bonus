/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:49:21 by rumachad          #+#    #+#             */
/*   Updated: 2024/06/25 11:56:29 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void minimap_tiles(t_mlx *mlx, t_map *map, int tile_size)
{
	int x;
	int y;
	int i;
	int j;

	i = -1;
	j = -1;
	y = -1;
	while (++y < map->height) 
	{
		x = -1;
		while (++x < (int)ft_strlen(map->game_map[y])) 
		{
			int color;
			if (map->game_map[y][x] == '0')
				color = 0x9c9c9c;
			else if(map->game_map[y][x] == 'D' || map->game_map[y][x] == 'd')
				color = 0x0050FF;
			else if (map->game_map[y][x] == 'X')
				color = 0xFFFFFF;
			else
				color = 0x000000;
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

void	map_objs(t_mlx *mlx, t_list *objs_lst, int tile_size, int i, int j)
{
	t_v2D	sprite;
	t_objs	*obj;
	int		color;

	while (objs_lst != NULL)
	{
		obj = (t_objs *)objs_lst->content;
		sprite = multiply_vector(obj->pos, tile_size);
		if (obj->type == ENEMY)
			color = 0xFF0000;
		else if (obj->type == COLLECT)
			color = 0xFFFF00;
		else if (obj->type == BALL)
			color = 0x0000FF;
		else if (obj->type == HP_COLLECT)
			color = 0x00FF00;
		pixel_put(&mlx->img, sprite.x + i, sprite.y + j, color);
		objs_lst = objs_lst->next;
	}	
}

void	draw_map_sprites(t_mlx *mlx, t_list *objs_lst, int tile_size)
{
	t_v2D	player;
	int sprite_size = tile_size / 2;
	int i;
	int	j;
	
	i = -sprite_size;
	player = multiply_vector(mlx->player.pos, tile_size);
	while (i < sprite_size) 
	{
		j = -sprite_size;
		while (j < sprite_size) 
		{
			objs_lst = mlx->objs_lst;
			map_objs(mlx, objs_lst, tile_size, i , j);
			pixel_put(&mlx->img, player.x + i, player.y + j, 0x00FFFF);
			j++;
		}
		i++;
	}
}

void draw_minimap(t_mlx *mlx, t_list *objs_lst)
{
	int minimap_size;
	int tile_size;
	
	minimap_size = 200;
	tile_size = minimap_size / 36;
	minimap_tiles(mlx, mlx->map, tile_size);
	draw_map_sprites(mlx, objs_lst, tile_size);
}
