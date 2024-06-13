/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 20:42:31 by rumachad          #+#    #+#             */
/*   Updated: 2024/06/13 11:58:45 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_v2D	sprite_dist(t_player *player, t_v2D pos)
{
	t_v2D	spr_vector;
	t_v2D	transform;
	double	inv;
	
	spr_vector.x = pos.x - player->pos.x;
	spr_vector.y = pos.y - player->pos.y;
	inv = 1 / (player->plane.x * player->direction.y
				- player->plane.y * player->direction.x);
	transform.x = inv * (player->direction.y * spr_vector.x
							- player->direction.x * spr_vector.y);
	transform.y = inv * (-player->plane.y * spr_vector.x
							+ player->plane.x * spr_vector.y);
	return (transform);
}

void	draw_sprite(t_v2D transform, t_mlx *mlx, t_image *sprite)
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
					int color = pixel_get(sprite, tex_x, tex_y);
					if (color != (int)0xFF00FF)
						pixel_put(&mlx->img, stripe, y, color);
				}
			}
		}
	}
}

void	lst_loop(t_mlx *mlx, t_list *objs_lst)
{
	t_v2D		s_dist;
	t_objs		*obj;
	
	s_dist = (t_v2D){0, 0};
	print_list(mlx->objs_lst);
	printf("\n");
	while (objs_lst != NULL)
	{
		obj = (t_objs *)objs_lst->content;
		/* printf("%d\n", );
		exit(0); */
		update_time(&mlx->current_time);
		obj->elapsed_time = time_passed(&obj->last_time, &mlx->current_time);
		s_dist = sprite_dist(&mlx->player, obj->pos);
		draw_sprite(s_dist, mlx, &mlx->sprite[obj->spr_index].img);
		objs_lst = objs_lst->next;
	}
}

void	sprite_loop(t_mlx *mlx)
{
	t_v2D		s_dist;
	int			char_anim;
	t_v2D		sprite_pos;

	s_dist = (t_v2D){0, 0};
	sprite_pos = (t_v2D){20, HEIGHT - 110};
	mlx->objs_lst = sort_sprites(&mlx->player, mlx->objs_lst);
	lst_loop(mlx, mlx->objs_lst);
	char_anim = calc_char_anim(mlx);
	if (mlx->player.hp <= 0)
	{
		sprite_pos = (t_v2D){(WIDTH/2) - 50, HEIGHT/2};
		draw_end_game(mlx);
		draw_char(mlx, char_anim, sprite_pos);
	}
	else
	{
		draw_char(mlx, char_anim, sprite_pos);
		draw_hp(mlx);
	}
	// print_vector(mlx->ball_pos);
}
