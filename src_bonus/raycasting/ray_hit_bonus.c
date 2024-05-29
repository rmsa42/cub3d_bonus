/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_hit_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 10:15:49 by rumachad          #+#    #+#             */
/*   Updated: 2024/05/29 12:49:17 by cacarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include <time.h>
#include <stdbool.h>

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
	static int i = 7;
	mlx->spr_index = 6;
	static struct timespec last_time = {0};
	struct timespec current_time;
	double elapsed_time;

	if (last_time.tv_sec == 0 && last_time.tv_nsec == 0)
		clock_gettime(CLOCK_MONOTONIC, &last_time);
	clock_gettime(CLOCK_MONOTONIC, &current_time);
	elapsed_time = (current_time.tv_sec - last_time.tv_sec) +
				(current_time.tv_nsec - last_time.tv_nsec) / 1e9;
	if (map->game_map[map->y][map->x] == 'd' )
	{
		mlx->spr_index = i;
		if (elapsed_time >= 0.35)
		{
			i++;
			clock_gettime(CLOCK_MONOTONIC, &last_time);
		}
	}
	if (i == 12)
		i = 7;
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

