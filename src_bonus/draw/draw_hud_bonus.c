/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hud_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:27:02 by rumachad          #+#    #+#             */
/*   Updated: 2024/06/27 14:11:29 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	draw_hud(t_mlx *mlx, int spr_index, t_v2D sprite_pos)
{
	t_v2D	scr;
	t_cell	texture;
	int		color;
	int		new_size;

	scr.y = sprite_pos.y;
	new_size = (int)(SPRITE_SIZE * 2)*((double)WIDTH / 800);
	while (++scr.y < sprite_pos.y + new_size)
	{
		scr.x = sprite_pos.x;
		texture.y = ((scr.y - (sprite_pos.y)) / 2) * (600 / (double)HEIGHT);
		while (++scr.x < sprite_pos.x + new_size)
		{
			texture.x = ((scr.x - sprite_pos.x) / 2) * (800 / (double)WIDTH);
			if (texture.x >= 0 && texture.x < SPRITE_SIZE && \
				texture.y >= 0 && texture.y < SPRITE_SIZE)
			{
				color = pixel_get(&mlx->sprite[spr_index].img, \
					texture.x, texture.y);
				if (color != TRANSPARENT)
					pixel_put(&mlx->img, scr.x, scr.y, color);
			}
		}
	}
}

void	custom_pixel_put(t_image *img, int pixelX, int pixelY, int color)
{
	char			*dst;
	unsigned int	dst_color;
	int				red;
	int				green;
	int				blue;

	dst = img->addr + (pixelY * img->line_length + pixelX * \
		(img->bits_per_pixel / 8));
	dst_color = *(unsigned int *)dst;
	red = (int)(((color >> 16) & 0xFF) * 0.3 + \
		((dst_color >> 16) & 0xFF) * 0.7);
	green = (int)(((color >> 8) & 0xFF) * 0.3 + \
		((dst_color >> 8) & 0xFF) * 0.7);
	blue = (int)((color & 0xFF) * 0.3 + \
		(dst_color & 0xFF) * 0.7);
	color = (color & 0xFF000000) | (red << 16) | (green << 8) | blue;
	*(unsigned int *)dst = color;
}

void	put_screen_textures(t_mlx *mlx, t_cell texture, int sprite, t_v2D scr)
{
	int	color;

	if (texture.x >= 0 && texture.x < 800 && \
		texture.y >= 0 && texture.y < 600)
	{
		if (sprite == DAMAGED)
		{
			color = DAMAGE_RED;
			custom_pixel_put(&mlx->img, scr.x, scr.y, color);
		}
		else if (sprite == HEALED)
		{
			color = HEAL_GREEN;
			custom_pixel_put(&mlx->img, scr.x, scr.y, color);
		}
		else
		{
			color = pixel_get(&mlx->sprite[sprite].img, \
				texture.x, texture.y);
			if (color != TRANSPARENT)
				pixel_put(&mlx->img, scr.x, scr.y, color);
		}
	}
}

void	draw_end_game(t_mlx *mlx, int sprite)
{
	t_v2D	scr;
	t_cell	texture;

	scr.y = -1;
	while (++scr.y < HEIGHT)
	{
		texture.y = (scr.y) * (600 / HEIGHT);
		scr.x = -1;
		while (++scr.x < WIDTH)
		{
			texture.x = (scr.x) * (800 / WIDTH);
			put_screen_textures(mlx, texture, sprite, scr);
		}
	}
}
