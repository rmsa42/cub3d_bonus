/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactions_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:07:09 by rumachad          #+#    #+#             */
/*   Updated: 2024/05/22 16:39:01 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

bool	in_reach(char **game_map, t_player *player)
{
	int	x;
	int	y;

	x = (int)(player->pos.x + player->direction.x);
	y = (int)(player->pos.y + player->direction.y);
	if (game_map[y][x] == 'D')
		return (true);
	return (false);	
}