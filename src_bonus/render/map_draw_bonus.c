/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_draw_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:20:48 by rumachad          #+#    #+#             */
/*   Updated: 2024/06/03 16:12:29 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_objs	init_obj(int x, int y)
{
	t_objs	obj;

	obj.type = ENEMIE;
	obj.state = 0;
	obj.pos = (t_v2D){x, y};
	return (obj);
}

void	draw_map(t_mlx *mlx, int *counter, char *tile, int x, int y)
{
	if ((*tile == 'N' || *tile == 'S' || *tile == 'W' || *tile == 'E'))
	{
		mlx->player = init_player(x + 0.5, y + 0.5, *tile);
		*tile = '0';
	}
	else if (*tile == 's')
	{
		mlx->objs[*counter] = init_obj(x, y);
		(*counter)++;
	}
}

void	map_draw(t_mlx *mlx)
{
	t_map	*map;
	int		obj_counter;

	map = &mlx->map;
	map->y = 0;
	obj_counter = 0;
	while (map->game_map[map->y])
	{
		map->x = 0;
		while (map->game_map[map->y][map->x])
		{
			draw_map(mlx, &obj_counter, &map->game_map[map->y][map->x], map->x, map->y);
			map->x++;
		}
		map->y++;
	}
}
