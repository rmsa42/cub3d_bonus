/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:27:35 by rumachad          #+#    #+#             */
/*   Updated: 2024/05/28 10:11:27 by rumachad         ###   ########.fr       */
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

void	draw_texture(t_mlx *mlx, int x)
{
	draw_ceiling(&mlx->img, &mlx->draw, mlx->sprite[CEILING_S].color, x);
	draw_walls(&mlx->img, &mlx->draw, &mlx->sprite[mlx->spr_index], x);
	draw_floor(&mlx->img, &mlx->draw, mlx->sprite[FLOOR_S].color, x);
}

void	draw_sprite_init(t_draw *draw, t_v2D transform, int res)
{	
	draw->line_height = fabs(HEIGHT / transform.y);
	draw->start = HEIGHT / 2 - res;
	if (draw->start < 0)
		draw->start = 0;
	draw->end = HEIGHT / 2 + res;
	if (draw->end > HEIGHT)
		draw->end = HEIGHT;
}

/* void	draw_sprite(t_mlx *mlx)
{
	t_player *player;
	t_v2D	spr;
	t_draw	draw[2];
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
	draw_sprite_init(&draw[0], transform, HEIGHT / 2);
	int spr_scree_x = (WIDTH / 2) * (1 + transform.x / transform.y);
	draw_sprite_init(&draw[1], transform, spr_scree_x);
	
	int stripe = draw[1].start;
	int y = 0;
	while (stripe < draw[1].end)
	{
		int tex_x = 256 * ((stripe - draw[1].start) * SPRITE_SIZE / draw[1].line_height) / 256;
		y = draw[0].start;
		if (transform.y > 0 && stripe > 0 && stripe < WIDTH)
		{
			while (y < draw[0].end)
			{
				int d = y * 256 - HEIGHT + draw[0].line_height * 128;
				int tex_y = ((d * SPRITE_SIZE) / draw[0].line_height) / 256;
				int color = pixel_get(&mlx->sprite[0].img, tex_x, tex_y);
				pixel_put(&mlx->img, y, stripe, color);
				y++;
			}
		}
		stripe++;
	}
		
} */
