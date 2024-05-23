/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactions_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:07:09 by rumachad          #+#    #+#             */
/*   Updated: 2024/05/23 12:41:45 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

bool	in_reach(char **game_map, t_player *player)
{
	int	x;
	int	y;

	if (game_map[(int)player->pos.y][(int)player->pos.x] == 'D')
		return (true);
	x = (int)(player->pos.x + player->direction.x);
	y = (int)(player->pos.y + player->direction.y);
	if (game_map[y][x] == 'D' && player->key)
		return (true);
	player->key = false;
	return (false);	
}