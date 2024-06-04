/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_events_sprite_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:38:32 by rumachad          #+#    #+#             */
/*   Updated: 2024/06/04 09:54:03 by rumachad         ###   ########.fr       */
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
	velocity = multiply_vector(dir, SPEED * 0.1);
	obj->pos = add_vector(obj->pos, velocity);
}

void	update_sprites(t_player *player, t_objs *objs, int nbr_sprites)
{
	int	i;

	i = 0;
	while (i < nbr_sprites)
	{
		sprite_move(player, &objs[i]);
		i++;
	}
}