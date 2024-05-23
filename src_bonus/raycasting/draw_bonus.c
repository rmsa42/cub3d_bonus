/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:27:35 by rumachad          #+#    #+#             */
/*   Updated: 2024/05/23 10:36:51 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	draw_ceiling(t_draw *draw, int x)
{
	int	y;
	int	color;

	y = -1;
	color = draw->sprite[4].color;
	while (++y < draw->start)
	{
		/* color = pixel_get(&mlx->sprite[4].img, x, y); */
		pixel_put(draw->img, x, y, color);
	}
}

void	draw_walls(t_draw *draw, int x)
{
	int	color;
	int	y;
	int	tex_y;
	
	y = draw->start;
	while (y < draw->end)
	{
		tex_y = (int)draw->tex_pos & (SPRITE_SIZE - 1);
		draw->tex_pos += draw->scale;
		color = pixel_get(&draw->sprite[draw->sprite_index].img, draw->tex_x, tex_y);
		pixel_put(draw->img, x, y, color);
		y++;
	}
}

void	draw_floor(t_draw *draw, int x)
{
	int	y;
	int	color;

	y = draw->end;
	color = draw->sprite[5].color;
	while (y < (int)HEIGHT)
	{
		pixel_put(draw->img, x, y, color);
		y++;
	}
}

void	draw_texture(t_draw *draw, int x)
{
	draw_ceiling(draw, x);
	draw_walls(draw, x);
	draw_floor(draw, x);
}
