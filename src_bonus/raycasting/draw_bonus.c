/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:27:35 by rumachad          #+#    #+#             */
/*   Updated: 2024/05/23 16:54:32 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	draw_ceiling(t_objs *obj, int x)
{
	int	y;
	int	color;

	y = -1;
	color = obj->sprite[4].color;
	while (++y < obj->draw.start)
	{
		pixel_put(obj->img, x, y, color);
	}
}

void	draw_walls(t_objs *obj, int x)
{
	int	color;
	int	y;
	int	tex_y;
	
	y = obj->draw.start;
	while (y < obj->draw.end)
	{
		tex_y = (int)obj->draw.tex_pos & (SPRITE_SIZE - 1);
		obj->draw.tex_pos += obj->draw.scale;
		color = pixel_get(&obj->sprite[obj->draw.sprite_index].img, obj->draw.tex_x, tex_y);
		pixel_put(obj->img, x, y, color);
		y++;
	}
}

void	draw_floor(t_objs *obj, int x)
{
	int	y;
	int	color;

	y = obj->draw.end;
	color = obj->sprite[5].color;
	while (y < (int)HEIGHT)
	{
		pixel_put(obj->img, x, y, color);
		y++;
	}
}

void	draw_door(t_objs *obj, int x)
{
	int	y;
	int	tex_y;
	int	color;

	y = obj->draw.start;
	while (y < obj->draw.end)
	{
		tex_y = (int)obj->draw.tex_pos & (SPRITE_SIZE - 1);
		obj->draw.tex_pos += obj->draw.scale;
		color = pixel_get(&obj->sprite[obj->draw.sprite_index].img, obj->draw.tex_x, tex_y);
		pixel_put(obj->img, x, y, color);
		y++;
	}
}

void	draw_texture(t_objs *obj, int x)
{
	/* draw_ceiling(obj, x); */
	if (obj->type == WALL)
	{
		draw_walls(obj, x);
	}
	else if (obj->type == DOOR)
	{
		draw_door(obj, x);
	}
	/* draw_floor(obj, x); */
}
