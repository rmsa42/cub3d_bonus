/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:19:06 by rumachad          #+#    #+#             */
/*   Updated: 2024/05/29 12:45:29 by cacarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	step_rays(t_map map, t_v2D start_pos, t_ray *ray)
{
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->side_d.x = (start_pos.x - map.x) * ray->delta.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_d.x = (map.x + 1.0 - start_pos.x) * ray->delta.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_d.y = (start_pos.y - map.y) * ray->delta.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_d.y = (map.y + 1.0 - start_pos.y) * ray->delta.y;
	}
}

void	launch_rays(t_mlx *mlx, t_v2D start_pos, int x)
{
	t_player	*player;

	player = &mlx->player;
	mlx->camera = 2 * x / (double)WIDTH - 1;
	mlx->ray.dir.x = player->direction.x + player->plane.x * mlx->camera;
	mlx->ray.dir.y = player->direction.y + player->plane.y * mlx->camera;
	mlx->ray.delta.x = fabs(1 / mlx->ray.dir.x);
	mlx->ray.delta.y = fabs(1 / mlx->ray.dir.y);
	mlx->map.x = (int)start_pos.x;
	mlx->map.y = (int)start_pos.y;
	step_rays(mlx->map, start_pos, &mlx->ray);
}

void	dda(t_mlx *mlx)
{
	int		hit;
	t_map	*map;
	t_ray	*ray;

	hit = 0;
	map = &mlx->map;
	ray = &mlx->ray;
	while (!hit)
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
		if (map->game_map[map->y][map->x] == '1')
		{
			hit = 1;
			mlx->spr_index = select_sprite(ray, mlx->side);
		}
		if (map->game_map[map->y][map->x] == 'D' || map->game_map[map->y][map->x] == 'd')
		{
			hit = 1;
			door_hit(mlx, map);
		}
	}
	mlx->draw = calculus(&mlx->ray, &mlx->player, mlx->side);
}

void	ft_grua(t_mlx *mlx)
{
	int		x;

	x = 0;
	mlx->side = 0;
	while (x < (int)WIDTH)
	{
		launch_rays(mlx, mlx->player.pos, x);
		dda(mlx);
		draw_line(mlx, x);
		x++;
	}
	/* draw_sprite(mlx); */
	image_to_window(mlx, mlx->img.img_ptr, 0, 0);
}
