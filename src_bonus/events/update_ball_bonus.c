/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_ball_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:56:03 by rumachad          #+#    #+#             */
/*   Updated: 2024/06/18 14:14:19 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

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
			if (obj->hp <= 0)
				elim_obj(objs_lst, iter);
			return (1);
		}
		iter = iter->next;
	}
	return (0);
}

void	ball_movement(t_mlx *mlx, t_player *player, char **game_map, t_objs *ball)
{
	t_v2D	velocity;

	velocity = (t_v2D){0, 0};
	if (ball_hit_obj(&mlx->objs_lst, player->ball_node))
	{
		player->shoot = false;
		elim_obj(&mlx->objs_lst, player->ball_node);
	}
	else if (game_map[(int)ball->pos.y][(int)ball->pos.x] != '1' &&
		game_map[(int)ball->pos.y][(int)ball->pos.x] != 'D')
	{
		velocity = multiply_vector(player->direction, BALL_SPEED * mlx->delta);
		ball->pos = add_vector(ball->pos, velocity);
	}
	else
	{
		player->shoot = false;
		elim_obj(&mlx->objs_lst, player->ball_node);
	}
}

void	update_ball(t_mlx *mlx, t_player *player, char **game_map)
{
	t_objs	*ball;
	static int i;

	ball = (t_objs *)player->ball_node->content;
	if (i++ >= 45)
		ball->spr_index = BALL2;
	else
		ball->spr_index = BALL1;
	if (i == 91)
		i = 0;
	ball_movement(mlx, player, game_map, ball);
}

t_list	*init_ball(t_list **head, t_player *player)
{
	t_list	*node;
	t_objs	*ball;
	
	player->shoot = true;
	player->anim = true;
	ball = init_obj((t_v2D){0, 0}, BALL1, 20, BALL);
	ball->pos.x = player->pos.x + player->direction.x * 0.5;
	ball->pos.y = player->pos.y + player->direction.y * 0.5;
	node = ft_lstnew((void *)ball);
	ft_lstadd_back(head, node);
	return (node);
}
