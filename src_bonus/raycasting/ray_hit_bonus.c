/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_hit_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 10:15:49 by rumachad          #+#    #+#             */
/*   Updated: 2024/05/28 13:50:52 by cacarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	select_sprite(t_ray *ray, int side)
{
	int	sprite_index;
	
	sprite_index = 0;
	if (side == 1)
	{
		if (ray->dir.y < 0)
			sprite_index = 0;
		else
			sprite_index = 1;
	}
	else if (side == 0)
	{
		if (ray->dir.x < 0)
			sprite_index = 2;
		else
			sprite_index = 3;
	}
	return (sprite_index);
}

void	door_hit(t_mlx *mlx, t_map	*map)
{
	
	mlx->spr_index = 6;
	if (map->game_map[map->y][map->x] == 'd')
		mlx->spr_index = 7;
	if (mlx->side == 0)
	{
		mlx->ray.side_d.x -= mlx->ray.delta.x / 2;
		if (mlx->ray.side_d.x > mlx->ray.side_d.y)
		{
			mlx->ray.side_d.y += mlx->ray.delta.y;
			mlx->side = 1;
			mlx->spr_index = select_sprite(&mlx->ray, mlx->side);
		}
		mlx->ray.side_d.x += mlx->ray.delta.x;
	}
	else
	{
		mlx->ray.side_d.y -= mlx->ray.delta.y / 2;
		if (mlx->ray.side_d.y > mlx->ray.side_d.x)
		{
			mlx->ray.side_d.x += mlx->ray.delta.x;
			mlx->side = 0;
			mlx->spr_index = select_sprite(&mlx->ray, mlx->side);
		}
		mlx->ray.side_d.y += mlx->ray.delta.y;
	}
}
