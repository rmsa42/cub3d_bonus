/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:27:35 by rumachad          #+#    #+#             */
/*   Updated: 2024/06/03 16:18:21 by rumachad         ###   ########.fr       */
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

void	draw_sprite(t_v2D transform, double *dist_buffer, t_sprite *sprite, t_image *img)
{
	int spriteScreen_x = (int)(WIDTH / 2) * (1 + transform.x / transform.y);
	int spriteHeight = abs((int)(HEIGHT / transform.y));
	
	// Y Axis
	int drawStartY = HEIGHT / 2 - spriteHeight / 2;
	if (drawStartY < 0)
		drawStartY = 0;
	int drawEndY = spriteHeight / 2 + HEIGHT / 2;
	if (drawEndY >= HEIGHT)	
		drawEndY = HEIGHT;

	// X Axis
	int drawStartX = -spriteHeight / 2 + spriteScreen_x;
	if (drawStartX < 0)
		drawStartX = 0;
	int drawEndX = spriteHeight / 2 + spriteScreen_x;
	if (drawEndX >= WIDTH)
		drawEndX = WIDTH;
	
	for (int stripe = drawStartX; stripe < drawEndX; stripe++)
	{
		int tex_x = (256 * (stripe - (-spriteHeight / 2 + spriteScreen_x)) * SPRITE_SIZE / spriteHeight) / 256;
		if (transform.y > 0 && stripe > 0 && stripe < WIDTH && transform.y < dist_buffer[stripe])
		{
			for (int y = drawStartY; y < drawEndY; y++)
			{
				int d = y * 256 - HEIGHT * 128 + spriteHeight * 128;
				int tex_y = ((d * SPRITE_SIZE) / spriteHeight) / 256;
				int color = pixel_get(&sprite->img, tex_x, tex_y);
				if (color != (int)0xFF00FF)
					pixel_put(img, stripe, y, color);
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
		draw_sprite(transform, mlx->dist_buffer, &mlx->sprite[13], &mlx->img);
		i++;
	}
}
