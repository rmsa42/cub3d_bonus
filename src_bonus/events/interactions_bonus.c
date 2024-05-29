/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactions_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:07:09 by rumachad          #+#    #+#             */
/*   Updated: 2024/05/29 14:02:30 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	interact_door(t_tile *tile, char **game_map, t_player *player)
{
	int		check_x;
	int		check_y;

	check_x = (int)tile->pos.x;
	check_y = (int)tile->pos.y;
	if (tile->type == DOOR)
		game_map[check_y][check_x] = 'd';
	else if (tile->type == DOOR_OPEN)
		game_map[check_y][check_x] = 'D';
	player->key = false;
}

t_tile	get_next_tile(char **game_map, t_player *player)
{
	t_tile	tile;
	int		check_x;
	int		check_y;
	
	check_x = (int)(player->pos.x + player->direction.x);
	check_y = (int)(player->pos.y + player->direction.y);
	if (game_map[check_y][check_x] == 'D')
		tile = (t_tile){DOOR, (t_v2D){check_x, check_y}};
	else if (game_map[check_y][check_x] == 'd')
		tile = (t_tile){DOOR_OPEN, (t_v2D){check_x, check_y}};
	else if (game_map[check_y][check_x] == '1')
		tile = (t_tile){WALL, (t_v2D){check_x, check_y}};
	else
		tile = (t_tile){FLOOR, (t_v2D){check_x, check_y}};
	return (tile);
}
