/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_objs_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:00:52 by cacarval          #+#    #+#             */
/*   Updated: 2024/06/18 14:59:06 by rumachad         ###   ########.fr       */
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
			if (obj->type == COLLECT && mlx->player.coins <= mlx->max_coins)
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
