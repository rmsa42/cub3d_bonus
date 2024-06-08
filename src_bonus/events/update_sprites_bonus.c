/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_sprites_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:38:32 by rumachad          #+#    #+#             */
/*   Updated: 2024/06/08 15:45:29 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	sprite_move(t_player *player, t_entity *entity)
{
	t_v2D	dir;
	t_v2D	velocity;

	dir.x = player->pos.x - entity->base.pos.x;
	dir.y = player->pos.y - entity->base.pos.y;
	dir = normalize_vector(dir);
	velocity = multiply_vector(dir, SPEED * 0.3);
	entity->base.pos = add_vector(entity->base.pos, velocity);
}

void	damage_player(t_player *player, t_entity *entity)
{
	if ((int)entity->base.pos.x == (int)player->pos.x && (int)entity->base.pos.y == (int)player->pos.y)
		player->hp -= 1;	
}

void	update_sprites(t_player *player, t_lst *entities)
{
	t_entity	*entity;
	
	while (entities != NULL)
	{
		entity = (t_entity *)entities->data;
		if (entity->state == 1)
			sprite_move(player, entity);
		damage_player(player, entity);
		entities = entities->next;
	}
}