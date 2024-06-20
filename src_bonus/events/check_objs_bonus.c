/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_objs_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:00:52 by cacarval          #+#    #+#             */
/*   Updated: 2024/06/20 11:01:23 by cacarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	collectable_delete(t_mlx *mlx, t_list **objs_lst, t_objs *obj)
{
	t_list	*delete;

	if (obj->type == COLLECT || obj->type == HP_COLLECT)
	{
		if(obj->type == HP_COLLECT && mlx->player.hp < 100)
		{
			mlx->player.hp +=25;
			if (mlx->player.hp > 100)
				mlx->player.hp = 100;
		}
		else if (obj->type == COLLECT)
			mlx->player.coins++;
		else
			return (0);
		delete = (*objs_lst);
		(*objs_lst) = (*objs_lst)->next;
		elim_obj(&mlx->objs_lst, delete);
		return (1);
	}
	return(0);
}

bool	check_objs_collision(t_mlx *mlx, t_list *objs_lst, t_v2D check)
{
	t_objs	*obj;
	bool	collision;

	collision = false;
	while (objs_lst)
	{
		obj = (t_objs *)objs_lst->content;
		if (((int)check.x == (int)obj->pos.x
				&& (int)check.y == (int)obj->pos.y))
		{
			if (collectable_delete(mlx, &objs_lst, obj))
				continue;
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
