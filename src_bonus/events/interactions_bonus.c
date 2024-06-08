/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactions_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:07:09 by rumachad          #+#    #+#             */
/*   Updated: 2024/06/08 14:50:48 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	interact_door(char **game_map, t_player *player)
{
	t_game_obj	tile;
	int			check_x;
	int			check_y;

	tile = get_next_tile(game_map, player);
	check_x = (int)tile.pos.x;
	check_y = (int)tile.pos.y;
	if (tile.type == DOOR)
		game_map[check_y][check_x] = 'd';
	else if (tile.type == DOOR_OPEN)
		game_map[check_y][check_x] = 'D';
}

t_game_obj	get_next_tile(char **game_map, t_player *player)
{
	t_game_obj	tile;
	int		check_x;
	int		check_y;
	
	check_x = (int)(player->pos.x + player->direction.x);
	check_y = (int)(player->pos.y + player->direction.y);
	if (game_map[check_y][check_x] == 'D')
		tile = (t_game_obj){DOOR, (t_v2D){check_x, check_y}};
	else if (game_map[check_y][check_x] == 'd')
		tile = (t_game_obj){DOOR_OPEN, (t_v2D){check_x, check_y}};
	else if (game_map[check_y][check_x] == '1')
		tile = (t_game_obj){WALL, (t_v2D){check_x, check_y}};
	else
		tile = (t_game_obj){FLOOR, (t_v2D){check_x, check_y}};
	return (tile);
}
