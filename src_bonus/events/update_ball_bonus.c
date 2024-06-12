/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_ball_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:56:03 by rumachad          #+#    #+#             */
/*   Updated: 2024/06/12 12:11:32 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	print_list(t_list *lst)
{
	t_objs	*obj;
	
	while (lst != NULL)
	{
		obj = (t_objs *)lst->content;
		if (obj->type == ENEMY)
			printf("Enemy\n");
		else if (obj->type == BALL)
			printf("Ball\n");
		else
			printf("Sprite\n");
		lst = lst->next;
	}
}

void	elim_obj(t_list **head, t_list *elim_obj)
{
	t_list	*temp;

	temp = *head;
	if (*head == elim_obj)
	{
		*head = elim_obj->next;
		free(elim_obj->content);
		free(elim_obj);
		return ;
	}
	while (temp->next && temp->next != elim_obj)
		temp = temp->next;
	if (temp->next == NULL)
		return ;
	temp->next = elim_obj->next;
	free(elim_obj->content);
	free(elim_obj);
	elim_obj = NULL;
}

int	ball_hit_obj(t_list **objs_lst, t_list *ball_node)
{
	t_objs	*obj;
	t_objs	*ball;
	t_list	*iter;

	obj = NULL;
	ball = (t_objs *)ball_node->content;
	iter = *objs_lst;
	while (iter)
	{
		obj = (t_objs *)iter->content;
		if (obj->type != BALL && (int)ball->pos.x == (int)obj->pos.x
			&& (int)ball->pos.y == (int)obj->pos.y)
		{
			obj->hp--;
			if (obj->hp == 0)
				elim_obj(objs_lst, iter);
			return (1);
		}
		iter = iter->next;
	}
	return (0);
}

void	update_ball(t_player *player, t_list **objs_lst, char **game_map)
{
	t_v2D	velocity;
	t_objs	*ball;
	
	velocity = (t_v2D){0, 0};
	ball = (t_objs *)player->ball_node->content;
	if (ball_hit_obj(objs_lst, player->ball_node))
	{
		player->shoot = false;
		elim_obj(objs_lst, player->ball_node);
	}
	else if (game_map[(int)ball->pos.y][(int)ball->pos.x] != '1' &&
		game_map[(int)ball->pos.y][(int)ball->pos.x] != 'D')
	{
		velocity = multiply_vector(player->direction, SPEED * 3);
		ball->pos = add_vector(ball->pos, velocity);
	}
	else
	{
		player->shoot = false;
		elim_obj(objs_lst, player->ball_node);
	}
}

t_list	*init_ball(t_list **head, t_player *player)
{
	t_list	*node;
	t_objs	*ball;
	
	player->shoot = true;
	player->anim = true;
	ball = init_obj(0, 0, 16, BALL);
	ball->pos.x = player->pos.x + player->direction.x * 0.5;
	ball->pos.y = player->pos.y + player->direction.y * 0.5;
	node = ft_lstnew((void *)ball);
	ft_lstadd_back(head, node);
	return (node);
}
