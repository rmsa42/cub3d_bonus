/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactions_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:07:09 by rumachad          #+#    #+#             */
/*   Updated: 2024/06/11 11:19:19 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	interact_door(char **game_map, t_player *player)
{
	t_type	tile;
	int		check_x;
	int		check_y;

	tile = get_next_tile(game_map, player);
	check_x = (int)player->pos.x + player->direction.x;
	check_y = (int)player->pos.y + player->direction.y;
	if (tile == DOOR)
		game_map[check_y][check_x] = 'd';
	else if (tile == DOOR_OPEN)
		game_map[check_y][check_x] = 'D';
}

t_type	get_next_tile(char **game_map, t_player *player)
{
	int		check_x;
	int		check_y;
	
	check_x = (int)(player->pos.x + player->direction.x);
	check_y = (int)(player->pos.y + player->direction.y);
	if (game_map[check_y][check_x] == 'D')
		return (DOOR);
	else if (game_map[check_y][check_x] == 'd')
		return (DOOR_OPEN);
	else if (game_map[check_y][check_x] == '1')
		return (WALL);
	return (FLOOR);
}
