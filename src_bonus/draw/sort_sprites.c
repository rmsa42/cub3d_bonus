/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:57:01 by rumachad          #+#    #+#             */
/*   Updated: 2024/06/13 12:00:09 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	compare_dist(t_v2D obj_pos1, t_v2D obj_pos2, t_v2D pl_pos)
{
	t_v2D	v1;
	t_v2D	v2;

	v1.x = pl_pos.x - obj_pos1.x;
	v1.y = pl_pos.y - obj_pos1.y;
	v2.x = pl_pos.x - obj_pos2.x;
	v2.y = pl_pos.y - obj_pos2.y;
	if (length_vector(v2) > length_vector(v1))
		return (1);
	return (0);
}

void	swap_node(t_list *objs_lst)
{
	void	*tmp;

	tmp = objs_lst->content;
	objs_lst->content = objs_lst->next->content;
	objs_lst->next->content = tmp;
}

t_list	*sort_sprites(t_player *player, t_list *objs_lst)
{
	t_objs	*curr;
	t_objs	*next;
	t_list	*head;

	head = objs_lst;
	while (objs_lst && objs_lst->next != NULL)
	{
		curr = (t_objs *)objs_lst->content;
		next = (t_objs *)objs_lst->next->content;
		if (compare_dist(curr->pos, next->pos, player->pos))
		{
			swap_node(objs_lst);
			if (curr->type == BALL)
				player->ball_node = objs_lst->next;
			else if (next->type == BALL)
				player->ball_node = objs_lst;
		}
		else
			objs_lst = objs_lst->next;
	}
	objs_lst = head;
	return (objs_lst);
}
