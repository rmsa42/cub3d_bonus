/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_sprites_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:38:32 by rumachad          #+#    #+#             */
/*   Updated: 2024/06/05 15:30:47 by cacarval         ###   ########.fr       */
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
	velocity = multiply_vector(dir, SPEED * 0.3);
	obj->pos = add_vector(obj->pos, velocity);
}

void	damage_player(t_player *player, t_objs *obj)
{
	if ((int)obj->pos.x == (int)player->pos.x && (int)obj->pos.y == (int)player->pos.y)
		player->hp -= 1;	
}

void	update_sprites(t_player *player, t_objs *objs)
{
	int	i;

	i = 0;
	while (objs != NULL)
	{
		if (objs->type == ENEMY)
		{
			if (objs->state == 1)
				sprite_move(player, objs);
			damage_player(player, objs);
		}
		objs = objs->next;
	}
}