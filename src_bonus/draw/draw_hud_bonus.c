/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hud_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:27:02 by rumachad          #+#    #+#             */
/*   Updated: 2024/06/08 15:30:43 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	draw_hp(t_mlx *mlx)
{
	t_v2D	scr;
	t_v2D	texture;
	int		color;

	scr.y = HEIGHT - 175;
	int new_size = (int)(SPRITE_SIZE * 2);
	int i;
	i = 0;
	if (mlx->player.hp > 75)
		i = 26;
	else if (mlx->player.hp <= 75 && mlx->player.hp > 50)
		i = 27;
	else if (mlx->player.hp <= 50 && mlx->player.hp > 25)
		i = 28;
	else
		i = 29;
	while (++scr.y < HEIGHT - 175 + new_size) {
		scr.x = 20;
		while (++scr.x < 20 + new_size) {
			texture.x = (int)((scr.x - 20) / 2);
			texture.y = (int)((scr.y - (HEIGHT - 175)) / 2);

			if (texture.x >= 0 && texture.x < SPRITE_SIZE && texture.y >= 0 && texture.y < SPRITE_SIZE) {
				color = pixel_get(&mlx->sprite[i].img, texture.x, texture.y);
				if (color != (int)0xFF00FF) {
					pixel_put(&mlx->img, scr.x, scr.y, color);
				}
			}
		}
	}
}

int	calc_char_anim(t_mlx *mlx)
{
	// static struct timespec last_time;
	// struct timespec current_time;
	// double elapsed_time;
	static int char_anim = 18;
	double chosen_time = 0.10;
	static int i = 0;

	if(mlx->player.shoot == true && i == 0 && mlx->player.anim == true)
	{
		i = 1;
		char_anim = 30;
	}
/* 	if (last_time.tv_sec == 0 && last_time.tv_nsec == 0)
		update_time(&last_time);
	update_time(&current_time);
	elapsed_time = time_passed(&last_time, &current_time); */
	if (mlx->elapsed_time >= chosen_time)
	{
		char_anim++;
		update_time(&mlx->last_time);
	}
	if (char_anim == 26 || char_anim == 38)
	{
		mlx->player.anim = false;
		i = 0;
		char_anim = 18;
	}
	return(char_anim);
}

void	draw_char(t_mlx *mlx, int char_anim)
{
	t_v2D	scr;
	t_v2D	texture;
	int		color;

	scr.y = HEIGHT - 110;
	int new_size = (int)(SPRITE_SIZE * 2);

	while (++scr.y < HEIGHT - 110 + new_size) {
		scr.x = 20;
		while (++scr.x < 20 + new_size) {
			texture.x = (int)((scr.x - 20) / 2);
			texture.y = (int)((scr.y - (HEIGHT - 110)) / 2);

			if (texture.x >= 0 && texture.x < SPRITE_SIZE && texture.y >= 0 && texture.y < SPRITE_SIZE) {
				color = pixel_get(&mlx->sprite[char_anim].img, texture.x, texture.y);
				if (color != (int)0xFF00FF) {
					pixel_put(&mlx->img, scr.x, scr.y, color);
				}
			}
		}
	}
}
