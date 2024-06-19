/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_objs_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:00:52 by cacarval          #+#    #+#             */
/*   Updated: 2024/06/19 11:01:24 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

bool	check_objs_collision(t_mlx *mlx, t_list *objs_lst, t_v2D check)
{
	t_objs	*obj;
	t_list	*delete;
	bool	collision;

	collision = false;
	while (objs_lst)
	{
		obj = (t_objs *)objs_lst->content;
		if (((int)check.x == (int)obj->pos.x
				&& (int)check.y == (int)obj->pos.y))
		{
			if (obj->type == COLLECT)
			{
				delete = objs_lst;
				objs_lst = objs_lst->next;
				elim_obj(&mlx->objs_lst, delete);
				mlx->player.coins++;
				continue ;
			}
			collision = true;
		}
		objs_lst = objs_lst->next;
	}
	return(collision);
}

void	interact_door(char **game_map, t_player *player)
{
	t_type	tile;
	int		check_x;
	int		check_y;

	tile = get_next_tile(game_map, player);
	check_x = (int)(player->pos.x + player->direction.x);
	check_y = (int)(player->pos.y + player->direction.y);
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
