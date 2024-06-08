/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_draw_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:20:48 by rumachad          #+#    #+#             */
/*   Updated: 2024/06/08 16:05:03 by rumachad         ###   ########.fr       */
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
	player.anim = false;
	player.shoot = false;
	player.hp = 100;
	return (player);
}

t_entity	init_entity(double x, double y, t_type type)
{
	t_entity	entity;

	entity.base.type = type;
	entity.base.pos = (t_v2D){x, y};
	entity.state = 0;
	entity.hp = 2;
	return (entity);
}

t_objs	init_obj(double x, double y, t_type type)
{
	t_objs	obj;

	obj.base.type = type;
	obj.base.pos = (t_v2D){x, y};
	obj.state = 0;
	return (obj);
}

void	draw_map(t_mlx *mlx, char *tile, int x, int y)
{
	t_lst		*node;
	t_objs		obj;
	t_entity	ent;

	node = NULL;
	if ((*tile == 'N' || *tile == 'S' || *tile == 'W' || *tile == 'E'))
	{
		mlx->player = init_player(x + 0.5, y + 0.5, *tile);
		*tile = '0';
	}
	else if (*tile == 's')
	{
		obj = init_obj(x + 0.5, y + 0.5, SPRITE);
		node = create_node((void *)&obj);
		lst_add_back(&mlx->objs_lst, node);
		*tile = '0';
	}
	else if (*tile == 'e')
	{
		ent = init_entity(x + 0.5, y + 0.5, ENEMY);
		node = create_node((void *)&ent);
		lst_add_back(&mlx->entities_lst, node);
		*tile = '0';
	}
}

void	prepare_map(t_mlx *mlx)
{
	t_map		*map;

	map = &mlx->map;
	map->y = 0;
	mlx->num_marked_cells = 0;
	mlx->marked_cells = (t_cell *)ft_calloc(mlx->map_height * mlx->map_height, sizeof(t_cell));
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
	lst_add_back(&mlx->union_list, mlx->objs_lst);
	lst_add_back(&mlx->union_list, mlx->entities_lst);
}
