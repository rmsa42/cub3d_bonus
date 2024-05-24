/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactions_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:07:09 by rumachad          #+#    #+#             */
/*   Updated: 2024/05/24 17:07:54 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

/* bool	in_reach(t_objs *objs, t_player *player)
{
	t_objs	*obj;
	double	next_x;
	double	next_y;

	next_x = (player->pos.x + player->direction.x);
	next_y = (player->pos.y + player->direction.y);
	return (true);
} */

void	open_door(t_tile *tile, char **game_map)
{
	int	check_x;
	int	check_y;

	check_x = (int)tile->pos.x;
	check_y = (int)tile->pos.y;
	game_map[check_y][check_x] = '0';
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
	else if (game_map[check_y][check_x] == '1')
		tile = (t_tile){WALL, (t_v2D){check_x, check_y}};
	else
		tile = (t_tile){FLOOR, (t_v2D){check_x, check_y}};
	return (tile);
}
