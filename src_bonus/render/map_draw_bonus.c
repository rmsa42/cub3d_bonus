/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_draw_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:20:48 by rumachad          #+#    #+#             */
/*   Updated: 2024/05/31 12:01:30 by cacarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	draw_map(t_mlx *mlx, char *tile, int x, int y)
{
	if ((*tile == 'N' || *tile == 'S' || *tile == 'W' || *tile == 'E'))
	{
		mlx->player = init_player(x + 0.5, y + 0.5, *tile);
		*tile = '0';
	}
/* 	else if (*tile == 's')
	{
		mlx->spr_pos = (t_v2D){x, y};
	} */
}

void	map_draw(t_mlx *mlx)
{
	t_map	*map;

	map = &mlx->map;
	map->y = 0;
	while (map->game_map[map->y])
	{
		map->x = 0;
		while (map->game_map[map->y][map->x])
		{
			draw_map(mlx, &map->game_map[map->y][map->x], map->x, map->y);
			map->x++;
		}
		map->y++;
	}
}
