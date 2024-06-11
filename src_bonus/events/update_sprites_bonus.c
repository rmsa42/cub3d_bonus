/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_sprites_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:38:32 by rumachad          #+#    #+#             */
/*   Updated: 2024/06/11 12:57:36 by cacarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	sprite_move(t_player *player, t_objs *obj)
{
	t_v2D	dir;
	t_v2D	velocity;

	dir.x = player->pos.x - obj->pos.x;
	dir.y = player->pos.y - obj->pos.y;
	dir = normalize_vector(dir);
	velocity = multiply_vector(dir, SPEED * 0.5);
	obj->pos = add_vector(obj->pos, velocity);
}

void	damage_player(t_player *player, t_objs *obj)
{
	if ((int)obj->pos.x == (int)player->pos.x && (int)obj->pos.y == (int)player->pos.y)
		player->hp -= 1;	
}

void	update_sprites(t_mlx *mlx, t_player *player, t_list *objs_lst)
{
	t_objs	*obj;
	
	(void)mlx;
	obj = NULL;
	while (objs_lst != NULL)
	{
		obj = (t_objs *)objs_lst->content;
		if (obj->state == 1)
		{
			sprite_move(player, obj);
			if(obj->elapsed_time >= 0.30 && obj->spr_index != 40)
			{
				obj->spr_index++;
				update_time(&obj->last_time);
			}
		}
		else if (obj->spr_index >= 40 && obj->spr_index != 42 && obj->elapsed_time >= 0.30)
		{
			obj->spr_index++;
			update_time(&obj->last_time);
		}
		if(obj->spr_index == 42)
			obj->spr_index = 38;
		damage_player(player, obj);
		objs_lst = objs_lst->next;
	}
}