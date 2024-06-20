/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_sprites_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:38:32 by rumachad          #+#    #+#             */
/*   Updated: 2024/06/19 14:27:42 by cacarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	update_sprite_anim(t_objs *obj)
{
	if (obj->spr_index == ENEMY_DOWN)
		obj->spr_index = ENEMY1;
	else if (obj->elapsed_time >= 0.20 && obj->spr_index != ENEMY_DOWN)
	{
		obj->spr_index++;
		update_time(&obj->last_time);
	}
}

void	sprite_move(t_player *player, t_objs *obj, double delta)
{
	t_v2D	dir;
	t_v2D	velocity;
	t_v2D	check;

	dir.x = player->pos.x - obj->pos.x;
	dir.y = player->pos.y - obj->pos.y;
	dir = normalize_vector(dir);
	check = dir;
	velocity = multiply_vector(dir, (PL_SPEED * 1) * delta);
	check = add_vector(obj->pos, multiply_vector(check, (PL_SPEED + 1) * delta));
	if ((int)check.x != (int)player->pos.x || (int)check.y != (int)player->pos.y)
	{
		obj->spr_index = ENEMY1;
		obj->pos = add_vector(obj->pos, velocity);
	}
	else
	{
		update_sprite_anim(obj);
		if (obj->spr_index == ENEMY3 && obj->elapsed_time >= 0.10)
			player->hp -= 2;
	}
}

void	update_sprites(t_mlx *mlx, t_player *player, t_list *objs_lst)
{
	t_objs	*obj;
	
	(void)mlx;
	obj = NULL;
	while (objs_lst != NULL)
	{
		obj = (t_objs *)objs_lst->content;
		if(obj->type == ENEMY)
		{
			if (obj->state == 1)
				sprite_move(player, obj, mlx->delta);
			else
				obj->spr_index = ENEMY1;
		}
		objs_lst = objs_lst->next;
	}
}
