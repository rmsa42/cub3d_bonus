/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_hit_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 10:15:49 by rumachad          #+#    #+#             */
/*   Updated: 2024/05/31 10:25:40 by cacarval         ###   ########.fr       */
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

double time_passed(struct timespec *last, struct timespec *current) 
{
    return (current->tv_sec - last->tv_sec) + (current->tv_nsec - last->tv_nsec) / 1e9;
}

void update_time(struct timespec *time)
{
	clock_gettime(CLOCK_MONOTONIC, time);
}

void	door_hit(t_mlx *mlx, t_map	*map)
{
	static int i = 7;
	mlx->spr_index = 6;
	static struct timespec last_time;
	struct timespec current_time;
	double elapsed_time;

	if (last_time.tv_sec == 0 && last_time.tv_nsec == 0)
		update_time(&last_time);
	update_time(&current_time);
	elapsed_time = time_passed(&last_time, &current_time);
	if (map->game_map[map->y][map->x] == 'd' )
	{
		mlx->spr_index = i;
		if (elapsed_time >= 0.35)
		{
			i++;
			update_time(&last_time);
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

