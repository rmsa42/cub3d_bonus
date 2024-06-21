/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_objs_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:00:52 by cacarval          #+#    #+#             */
/*   Updated: 2024/06/21 12:23:22 by cacarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	collectable_delete(t_mlx *mlx, t_list **objs_lst, t_objs *obj)
{
	t_list	*delete;

	if (obj->type == COLLECT || obj->type == HP_COLLECT)
	{
		if (obj->type == HP_COLLECT && mlx->player.hp < 100)
		{
			mlx->player.hp += 25;
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

bool	is_obj_collision(t_v2D check, t_v2D obj_pos)
{
	int	x;
	int	y;

	x = (int)check.x;
	y = (int)check.y;
	if (x == (int)obj_pos.x && y == (int)obj_pos.y)
		return (true);
	return (false);
}

bool is_wall_collision(t_map map, float x, float y)
{
	int map_x;
	int map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map.game_map[map_y][map_x] == '1' || map.game_map[map_y][map_x] == 'D'
		|| map.game_map[map_y][map_x] == 'P')
		return true;
	return false;
}

bool	check_objs_collision(t_mlx *mlx, t_list *objs_lst, t_v2D check)
{
	t_objs	*obj;
	bool	collision;

	collision = false;
	while (objs_lst)
	{
		obj = (t_objs *)objs_lst->content;
		if (is_obj_collision(check, obj->pos))
		{
			if (collectable_delete(mlx, &objs_lst, obj))
				continue;
			collision = true;
		}
		objs_lst = objs_lst->next;
	}
	return (collision);
}
