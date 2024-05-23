/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:19:06 by rumachad          #+#    #+#             */
/*   Updated: 2024/05/23 11:10:58 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	step_rays(t_map map, t_player player, t_ray *ray)
{
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->side_d.x = (player.pos.x - map.x) * ray->delta.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_d.x = (map.x + 1.0 - player.pos.x) * ray->delta.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_d.y = (player.pos.y - map.y) * ray->delta.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_d.y = (map.y + 1.0 - player.pos.y) * ray->delta.y;
	}
}

void	launch_rays(t_mlx *mlx, int x)
{
	t_player	*player;

	player = &mlx->player;
	mlx->camera = 2 * x / (double)WIDTH - 1;
	mlx->ray.dir.x = player->direction.x + player->plane.x * mlx->camera;
	mlx->ray.dir.y = player->direction.y + player->plane.y * mlx->camera;
	mlx->ray.delta.x = fabs(1 / mlx->ray.dir.x);
	mlx->ray.delta.y = fabs(1 / mlx->ray.dir.y);
	mlx->map.x = (int)player->pos.x;
	mlx->map.y = (int)player->pos.y;
	step_rays(mlx->map, mlx->player, &mlx->ray);
}

void	select_sprite(t_ray *ray,  int *sprite_index, int side)
{
	if (side == 1)
	{
		if (ray->dir.y < 0)
			*sprite_index = 0;
		else
			*sprite_index = 1;
	}
	else if(side == 0)
	{
		if (ray->dir.x < 0)
			*sprite_index = 2;
		else
			*sprite_index = 3;
	}
}

void	door_hit(t_ray *ray, int *sprite_index, int *side)
{
	*sprite_index = 6;
	if (*side == 0)
	{
		ray->side_d.x -= ray->delta.x / 2;
		if (ray->side_d.x > ray->side_d.y)
		{
			ray->side_d.y += ray->delta.y;
			*side = 1;
			select_sprite(ray, sprite_index, *side);
		}
		ray->side_d.x += ray->delta.x;
	}
	else
	{
		ray->side_d.y -= ray->delta.y / 2;
		if (ray->side_d.y > ray->side_d.x)
		{
			ray->side_d.x += ray->delta.x;
			*side = 0;
			select_sprite(ray, sprite_index, *side);
		}
		ray->side_d.y += ray->delta.y;
	}
}

void	dda(t_mlx *mlx, t_map *map, t_ray *ray, int *sprite_index)
{
	int	hit;

	hit = 0;
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
			select_sprite(ray, sprite_index, mlx->side);
		}
		if (map->game_map[map->y][map->x] == 'D'/*  && mlx->player.open_door == false */)
		{
			hit = 1;
			door_hit(ray, sprite_index, &mlx->side);
		}
	}
}

int	text_x(t_ray *ray, int side, double perp_wall, t_player *player)
{
	double	wall_x;
	int		tex_x;

	wall_x = 0;
	tex_x = 0;
	if (side == 0)
		wall_x = player->pos.y + perp_wall * ray->dir.y;
	else
		wall_x = player->pos.x + perp_wall * ray->dir.x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (int)SPRITE_SIZE);
	if ((side == 0 && ray->dir.x < 0) || (side == 1 && ray->dir.y > 0))
		tex_x = SPRITE_SIZE - tex_x - 1;
	return (tex_x);
}

void	calculus(t_draw *draw, t_player *player, t_ray *ray, int side)
{
	double	perp_wall;

	perp_wall = 0;
	if (side == 0)
		perp_wall = (ray->side_d.x - ray->delta.x);
	else
		perp_wall = (ray->side_d.y - ray->delta.y);
	draw->tex_x = text_x(ray, side, perp_wall, player);
	draw->line_height = fabs(HEIGHT / perp_wall);
	draw->start = (HEIGHT / 2 - draw->line_height / 2) + player->pitch;
	if (draw->start < 0)
		draw->start = 0;
	draw->end = (HEIGHT / 2 + draw->line_height / 2) + player->pitch;
	if (draw->end >= HEIGHT)
		draw->end = HEIGHT;
	draw->scale = SPRITE_SIZE / draw->line_height;
	draw->tex_pos = (draw->start - player->pitch - HEIGHT / 2 +
			draw->line_height / 2) * draw->scale;
}

void	ft_grua(t_mlx *mlx)
{
	int		x;
	t_draw	draw;

	x = 0;
	mlx->side = 0;
	draw.img = &mlx->img;
	draw.sprite = mlx->sprite;
	while (x < (int)WIDTH)
	{
		launch_rays(mlx, x);
		dda(mlx, &mlx->map, &mlx->ray, &draw.sprite_index);
		calculus(&draw, &mlx->player, &mlx->ray, mlx->side);
		draw_texture(&draw, x);
		x++;
	}
	image_to_window(mlx, mlx->img.img_ptr, 0, 0);
}
