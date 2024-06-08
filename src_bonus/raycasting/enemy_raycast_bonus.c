/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_raycast_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:24:23 by rumachad          #+#    #+#             */
/*   Updated: 2024/06/08 15:14:07 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	enemy_step_rays(t_map map, t_v2D *pos, t_ray *ray)
{
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->side_d.x = (pos->x - map.x) * ray->delta.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_d.x = (map.x + 1.0 - pos->x) * ray->delta.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_d.y = (pos->y - map.y) * ray->delta.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_d.y = (map.y + 1.0 - pos->y) * ray->delta.y;
	}
}

void	enemy_dda(t_mlx *mlx, t_entity *entity)
{
	int		hit;
	t_ray	*ray;
	t_map	*map;

	hit = 0;
	ray = &mlx->ray;
	map = &mlx->map;
	while (hit != 1)
	{
		if (ray->side_d.x < ray->side_d.y)
		{
			ray->side_d.x += ray->delta.x;
			map->x += ray->step.x;
			mlx->side = 0;
		}
		else
		{
			ray->side_d.y += ray->delta.y;
			map->y += ray->step.y;
			mlx->side = 1;
		}
		if (map->game_map[map->y][map->x] == '1' ||
			map->game_map[map->y][map->x] == 'D' ||
			map->game_map[map->y][map->x] == 'd')
		{
			entity->state = 0;
			hit = 1;
		}
		else if (map->x == (int)mlx->player.pos.x &&
				map->y == (int)mlx->player.pos.y)
		{
			entity->state = 1;
			hit = 1;
		}
	}
}

void	enemy_ray(t_mlx *mlx)
{
	t_player	*player;
	t_lst		*ents;
	t_entity	*entity;

	ents = mlx->entities_lst;
	player = &mlx->player;
	while (ents != NULL)
	{
		entity = (t_entity *)ents->data;
		mlx->ray.dir.x = player->pos.x - entity->base.pos.x;
		mlx->ray.dir.y = player->pos.y - entity->base.pos.y;
		mlx->ray.delta.x = fabs(1 / mlx->ray.dir.x);
		mlx->ray.delta.y = fabs(1 / mlx->ray.dir.y);
		mlx->map.x = (int)entity->base.pos.x;
		mlx->map.y = (int)entity->base.pos.y;
		enemy_step_rays(mlx->map, &entity->base.pos, &mlx->ray);
		enemy_dda(mlx, entity);
		ents = ents->next;
	}
}
