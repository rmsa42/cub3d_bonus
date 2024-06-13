/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_sprites_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:38:32 by rumachad          #+#    #+#             */
/*   Updated: 2024/06/13 10:24:47 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	sprite_move(t_player *player, t_objs *obj)
{
	t_v2D	dir;
	t_v2D	velocity;
	t_v2D	check;

	dir.x = player->pos.x - obj->pos.x;
	dir.y = player->pos.y - obj->pos.y;
	dir = normalize_vector(dir);
	check = dir;
	velocity = multiply_vector(dir, SPEED * 0.7);
	check = add_vector(obj->pos, multiply_vector(check, SPEED + 0.6));
	if ((int)check.x != (int)player->pos.x || (int)check.y != (int)player->pos.y)
	{
		obj->spr_index = 38;
		obj->pos = add_vector(obj->pos, velocity);
	}
	else
	{
		if(obj->elapsed_time >= 0.30 && obj->spr_index  !=42)
		{
			obj->spr_index++;
			update_time(&obj->last_time);
		}
		if(obj->spr_index == 42)
			obj->spr_index = 38;
		if(obj->spr_index == 40 && obj->elapsed_time >= 0.10)	
			player->hp -= 1;
	}
}

// void	damage_player(t_player *player, t_objs *obj)
// {
// 	if ((int)obj->pos.x == (int)player->pos.x && (int)obj->pos.y == (int)player->pos.y && obj->spr_index == 40)
// 		player->hp -= 1;	
// }

void	update_sprites(t_mlx *mlx, t_player *player, t_list *objs_lst)
{
	t_objs	*obj;
	
	(void)mlx;
	obj = NULL;
	while (objs_lst != NULL)
	{
		obj = (t_objs *)objs_lst->content;
		if (obj->type == ENEMY)
		{
			if (obj->state == 1)
				sprite_move(player, obj);
			else
				obj->spr_index = 38;
	/* 		damage_player(player, obj); */	
		}
		objs_lst = objs_lst->next;
	}
}
