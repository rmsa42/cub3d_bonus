/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_draw_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:20:48 by rumachad          #+#    #+#             */
/*   Updated: 2024/06/04 12:25:33 by cacarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_player	init_player(double x, double y, char tile)
{
	t_player	player;
	int			dir;

	player.pitch = 0;
	dir = 1;
	player.pos = (t_v2D){x, y};
	if (tile == 'N')
		player.direction = (t_v2D){0, -dir};
	else if (tile == 'S')
		player.direction = (t_v2D){0, dir};
	else if (tile == 'W')
		player.direction = (t_v2D){-dir, 0};
	else if (tile == 'E')
		player.direction = (t_v2D){dir, 0};
	player.movement = (t_v2D){0, 0};
	player.plane = perp_vector(player.direction);
	player.angle = 0.1;
	player.fov = (double)FOV / 90;
	player.key = false;
	return (player);
}

t_objs	init_obj(int x, int y)
{
	t_objs	obj;

	obj.type = ENEMIE;
	obj.state = 0;
	obj.pos = (t_v2D){x, y};
	return (obj);
}

void	draw_map(t_mlx *mlx, char *tile, int x, int y)
{
	if ((*tile == 'N' || *tile == 'S' || *tile == 'W' || *tile == 'E'))
	{
		mlx->player = init_player(x + 0.5, y + 0.5, *tile);
		*tile = '0';
	}
	else if (*tile == 's')
	{
		mlx->objs[mlx->nbr_sprites] = init_obj(x, y);
		*tile = '0';
		mlx->nbr_sprites++;
	}
}

void	prepare_map(t_mlx *mlx)
{
	t_map		*map;

	map = &mlx->map;
	map->y = 0;
	mlx->nbr_sprites = 0;
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
