/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:27:35 by rumachad          #+#    #+#             */
/*   Updated: 2024/06/04 09:57:27 by rumachad         ###   ########.fr       */
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

void	draw_walls(t_image *img, t_draw *draw, t_sprite *sprite, int x)
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
	draw_ceiling(&mlx->img, &mlx->draw, mlx->sprite[C].color, x);
	draw_walls(&mlx->img, &mlx->draw, &mlx->sprite[mlx->spr_index], x);
	draw_floor(&mlx->img, &mlx->draw, mlx->sprite[F].color, x);
}