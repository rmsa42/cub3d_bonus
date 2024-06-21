/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hud_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:27:02 by rumachad          #+#    #+#             */
/*   Updated: 2024/06/21 13:14:16 by cacarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	draw_hud(t_mlx *mlx, int spr_index, t_v2D sprite_pos)
{
	t_v2D	scr;
	t_v2D	texture;
	int		color;
	int		new_size;

	scr.y = sprite_pos.y;
	new_size = (int)(SPRITE_SIZE * 2);
	while (++scr.y < sprite_pos.y + new_size)
	{
		scr.x = sprite_pos.x;
		while (++scr.x < sprite_pos.x + new_size)
		{
			texture.x = (int)((scr.x - sprite_pos.x) / 2);
			texture.y = (int)((scr.y - (sprite_pos.y)) / 2);
			if (texture.x >= 0 && texture.x < SPRITE_SIZE && texture.y >= 0 && texture.y < SPRITE_SIZE)
			{
				color = pixel_get(&mlx->sprite[spr_index].img, texture.x, texture.y);
				if (color != (int)0xFF00FF)
					pixel_put(&mlx->img, scr.x, scr.y, color);
			}
		}
	}
}

void draw_end_game(t_mlx *mlx, int	sprite) 
{
	t_v2D	scr;
	t_v2D	texture;
	int		color;

	scr.y = -1;
	while (++scr.y <HEIGHT)
	{
		scr.x = -1;
		while (++scr.x < WIDTH)
		{
			texture.x = (int)(scr.x);
			texture.y = (int)(scr.y);
			if (texture.x >= 0 && texture.x < WIDTH && texture.y >= 0 && texture.y < HEIGHT)
			{
				color = pixel_get(&mlx->sprite[sprite].img, texture.x, texture.y);
				if (color != (int)0xFF00FF)
					pixel_put(&mlx->img, scr.x, scr.y, color);
			}
		}
	}
}
