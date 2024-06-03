/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 20:42:31 by rumachad          #+#    #+#             */
/*   Updated: 2024/06/03 23:21:23 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_v2D	trans_calc(t_player *player, t_objs *obj)
{
	t_v2D	spr_vector;
	t_v2D	transform;
	double	inv;
	
	spr_vector.x = obj->pos.x - player->pos.x;
	spr_vector.y = obj->pos.y - player->pos.y;
	inv = 1 / (player->plane.x * player->direction.y
				- player->plane.y * player->direction.x);
	transform.x = inv * (player->direction.y * spr_vector.x
							- player->direction.x * spr_vector.y);
	transform.y = inv * (-player->plane.y * spr_vector.x
							+ player->plane.x * spr_vector.y);
	return (transform);
}

void	draw_sprite(t_v2D transform, t_mlx *mlx)
{
	int spriteScreen_x = (int)(WIDTH / 2) * (1 + transform.x / transform.y);
	int spriteHeight = abs((int)(HEIGHT / transform.y));
	
	int drawStartY = (-spriteHeight / 2 + HEIGHT / 2) + mlx->player.pitch;
	if (drawStartY < 0)
		drawStartY = 0;
	int drawEndY = (spriteHeight / 2 + HEIGHT / 2) + mlx->player.pitch;
	if (drawEndY >= HEIGHT)	
		drawEndY = HEIGHT;
	int drawStartX = -spriteHeight / 2 + spriteScreen_x;
	if (drawStartX < 0)
		drawStartX = 0;
	int drawEndX = spriteHeight / 2 + spriteScreen_x;
	if (drawEndX >= WIDTH)
		drawEndX = WIDTH;
	
	for (int stripe = drawStartX; stripe < drawEndX; stripe++)
	{
		int tex_x = (256 * (stripe - (-spriteHeight / 2 + spriteScreen_x)) * SPRITE_SIZE / spriteHeight) / 256;
		if (transform.y > 0 && stripe > 0 && stripe < WIDTH && transform.y < mlx->dist_buffer[stripe])
		{
			for (int y = drawStartY; y < drawEndY; y++)
			{
				int d = y * 256 - HEIGHT * 128 + spriteHeight * 128 - mlx->player.pitch * 256;
				int tex_y = ((d * SPRITE_SIZE) / spriteHeight) / 256;
				
				if (tex_y >= 0 && tex_y < SPRITE_SIZE) {
					int color = pixel_get(&mlx->sprite[13].img, tex_x, tex_y);
					if (color != (int)0xFF00FF)
						pixel_put(&mlx->img, stripe, y, color);
				}
			}
		}
	}
}

void	sprite_loop(t_mlx *mlx)
{
	t_v2D	transform;
	int	i;
	
	i = 0;
	while (i < 6)
	{
		transform = trans_calc(&mlx->player, &mlx->objs[i]);
		draw_sprite(transform, mlx);
		i++;
	}
}