/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hud_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:27:02 by rumachad          #+#    #+#             */
/*   Updated: 2024/06/21 15:20:11 by cacarval         ###   ########.fr       */
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

void custom_pixel_put(t_image *img, int pixelX, int pixelY, int color)
{
    char *dst = img->addr + (pixelY * img->line_length + pixelX * (img->bits_per_pixel / 8));
    unsigned int *dst_pixel = (unsigned int *)dst;
    unsigned int dst_color = *dst_pixel;

    float alpha_src = (float)((color >> 24) & 0xFF) / 255.0f;
    float alpha_dst = 1.0f - alpha_src;

    int red = (int)(((color >> 16) & 0xFF) * alpha_src + ((dst_color >> 16) & 0xFF) * alpha_dst);
    int green = (int)(((color >> 8) & 0xFF) * alpha_src + ((dst_color >> 8) & 0xFF) * alpha_dst);
    int blue = (int)((color & 0xFF) * alpha_src + (dst_color & 0xFF) * alpha_dst);
  	color = (color & 0xFF000000) | (red << 16) | (green << 8) | blue;
    *dst_pixel = color;
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
				if (sprite == DAMAGED)
				{
					color = 0x4Dff0000;
					custom_pixel_put(&mlx->img, scr.x, scr.y, color);
				}
				else if (sprite == HEALED)
				{
					color = 0x4D00FF00;
					custom_pixel_put(&mlx->img, scr.x, scr.y, color);
				}
				else
				{
					color = pixel_get(&mlx->sprite[sprite].img, texture.x, texture.y);
					if (color != (int)0xFF00FF)
						pixel_put(&mlx->img, scr.x, scr.y, color);

				}
			}
		}
	}
}
