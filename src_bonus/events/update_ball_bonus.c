/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_ball_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:56:03 by rumachad          #+#    #+#             */
/*   Updated: 2024/06/11 17:07:29 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	elim_enemy(t_list **head, t_list *last, t_list *elim_obj)
{
	if (last == elim_obj)
		*head = elim_obj->next;
	else if (elim_obj->next)
		last->next = elim_obj->next;
	else
		last->next = NULL;
	free(elim_obj->content);
	free(elim_obj);
	printf("1234\n");
	elim_obj = NULL;
}

void	ball_hit_obj(t_list **objs_lst, t_v2D *ball_pos, bool *shoot)
{
	t_objs	*obj;
	t_list	*last;
	t_list	*iter;

	obj = NULL;
	iter = *objs_lst;
	last = iter;
	while (iter)
	{
		obj = (t_objs *)iter->content;
		if ((int)ball_pos->x == (int)obj->pos.x
			&& (int)ball_pos->y == (int)obj->pos.y)
		{
			if (obj->hp == 0)
				elim_enemy(objs_lst, last, iter);
			obj->hp--;
			*shoot = false;
		}
		last = iter;
		iter = iter->next;
	}
}

void	update_ball(t_player *player, t_list **objs_lst, char **game_map)
{
	t_v2D	velocity;
	
	ball_hit_obj(objs_lst, &player->ball_pos, &player->shoot);
	velocity = (t_v2D){0, 0};
	if (game_map[(int)player->ball_pos.y][(int)player->ball_pos.x] != '1' &&
		game_map[(int)player->ball_pos.y][(int)player->ball_pos.x] != 'D')
	{
		velocity = multiply_vector(player->direction, SPEED * 3);
		player->ball_pos = add_vector(player->ball_pos, velocity);
	}
	else
		player->shoot = false;
}
