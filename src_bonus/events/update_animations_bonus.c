/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_animations_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 13:39:53 by rumachad          #+#    #+#             */
/*   Updated: 2024/06/18 14:28:06 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	calc_char_anim(t_mlx *mlx)
{
	static int char_anim = CHARACTER1;
	double chosen_time = 0.10;
	static int i = 0;

	if (mlx->game_state == DIED_STATE && i == 0)
	{
		char_anim = DYING1;
		i = 1;
	}
	else if (mlx->player.shoot == true && i == 0 && mlx->player.anim)
	{
		i = 1;
		char_anim = ATTACK1;
	}
	else if (mlx->elapsed_time >= chosen_time && char_anim < 51)
	{
		char_anim++;
		update_time(&mlx->last_time);
	}
	if (char_anim == HP1 || char_anim == ENEMY1)
	{
		mlx->player.anim = false;
		i = 0;
		char_anim = CHARACTER1;
	}
	return (char_anim);
}

void	update_animations(t_mlx *mlx)
{
	t_player	*player;
	double		chosen_time;

	chosen_time = 0.10;
	player = &mlx->player;
	mlx->spr_character_index = calc_char_anim(mlx);
	mlx->spr_hp_index = HP4 - (player->hp / HP1);
	mlx->spr_coins_index = COINS1 + player->coins;
}
