/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_extra_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 09:53:20 by rumachad          #+#    #+#             */
/*   Updated: 2024/06/27 13:43:23 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	draw_hearts(t_mlx *mlx)
{
	t_v2D	sprite_pos;

	sprite_pos = (t_v2D){20 * WIDTH / 800, HEIGHT - (175 * HEIGHT / 600)};
	draw_hud(mlx, mlx->spr_hp_index, sprite_pos);
}

void	draw_coins(t_mlx *mlx)
{
	t_v2D	sprite_pos;

	sprite_pos = (t_v2D){WIDTH - (150 * WIDTH / 800), -30 * HEIGHT / 600};
	draw_hud(mlx, mlx->spr_coins_index, sprite_pos);
}

void	draw_char(t_mlx *mlx)
{
	t_v2D	sprite_pos;

	sprite_pos = (t_v2D){20 * WIDTH / 800, HEIGHT - (110 * HEIGHT / 600)};
	draw_hud(mlx, mlx->spr_character_index, sprite_pos);
}

void	end_game_screen(t_mlx *mlx)
{
	t_v2D	sprite_pos;

	sprite_pos = (t_v2D){(WIDTH / 2) - SPRITE_SIZE, HEIGHT / 2};
	draw_end_game(mlx, END_GAME);
	draw_hud(mlx, mlx->spr_character_index, sprite_pos);
}

void	end_game(t_mlx *mlx)
{
	update_animations(mlx);
	if (mlx->game_state == DIED_STATE)
		end_game_screen(mlx);
	else if (mlx->game_state == WIN_STATE)
		draw_end_game(mlx, WIN_GAME);
}
