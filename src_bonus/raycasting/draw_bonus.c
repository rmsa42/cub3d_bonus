/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:27:35 by rumachad          #+#    #+#             */
/*   Updated: 2024/06/03 15:51:06 by cacarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	draw_ceiling(t_image *img, t_draw *draw, int color, int x)
{
	int	y;

	y = -1;
	while (++y < draw->start)
	{
		pixel_put(img, x, y, color);
	}
}

void	draw_walls(t_mlx *mlx, t_image *img, t_draw *draw, t_sprite *sprite, int x)
{
	int	color;
	int	y;
	int	tex_y;
	
	y = draw->start;
	while (y < draw->end)
	{
		tex_y = (int)draw->tex_pos & (SPRITE_SIZE - 1);
		draw->tex_pos += draw->scale;
		color = pixel_get(&sprite->img, draw->tex_x, tex_y);
		if (color == (int)0xFFFFFF)
			color = mlx->sprite[1].color;
		pixel_put(img, x, y, color);
		y++;
	}
}

void	draw_floor(t_image *img, t_draw *draw, int color, int x)
{
	int	y;

	y = draw->end;
	while (y < (int)HEIGHT)
	{
		pixel_put(img, x, y, color);
		y++;
	}
}

void	draw_line(t_mlx *mlx, int x)
{
	draw_ceiling(&mlx->img, &mlx->draw, mlx->sprite[CEILING_S].color, x);
	draw_walls(mlx, &mlx->img, &mlx->draw, &mlx->sprite[mlx->spr_index], x);
	draw_floor(&mlx->img, &mlx->draw, mlx->sprite[FLOOR_S].color, x);
}

void	draw_sprite(t_mlx *mlx)
{
	t_player *player;
	t_v2D	spr;
	double	inv;
	t_v2D	transform;

	player = &mlx->player;
	spr.x = mlx->spr_pos.x - player->pos.x;
	spr.y = mlx->spr_pos.y - player->pos.y;
	inv = 1 / (player->plane.x * player->direction.y
				- player->plane.y * player->direction.x);
	transform.x = inv * (player->direction.y * spr.x
							- player->direction.x * spr.y);
	transform.y = inv * (-player->plane.y * spr.x
							+ player->plane.x * spr.y);
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
				int d = y * 256 - HEIGHT * 128 + spriteHeight * 128 - player->pitch * 256;
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


