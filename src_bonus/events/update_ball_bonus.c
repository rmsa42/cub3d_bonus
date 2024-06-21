/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_ball_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:56:03 by rumachad          #+#    #+#             */
/*   Updated: 2024/06/21 01:12:01 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ball_movement(t_mlx *mlx, t_player *player, t_objs *ball)
{
	t_v2D	velocity;

	velocity = multiply_vector(player->direction, BALL_SPEED * mlx->delta);
	ball->pos = add_vector(ball->pos, velocity);
}

void	update_ball(t_mlx *mlx, t_player *player)
{
	t_objs	*ball;
	t_list	*hit;

	ball = (t_objs *)player->ball_node->content;
	hit = ball_hit_obj(mlx->objs_lst, ball);
	if (hit || ball_hit_wall(mlx->map, ball))
	{
		clean_hit(&mlx->objs_lst, player, hit);
		return ;
	}
	ball_animation(ball);
	ball_movement(mlx, player, ball);
}

t_list	*init_ball(t_list **head, t_player *player)
{
	t_list	*node;
	t_objs	*ball;
	
	ball = init_obj((t_v2D){0, 0}, BALL1, 20, BALL);
	ball->pos.x = player->pos.x + player->direction.x * 0.3;
	ball->pos.y = player->pos.y + player->direction.y * 0.3;
	player->shoot = true;
	player->anim = true;
	node = ft_lstnew((void *)ball);
	ft_lstadd_back(head, node);
	return (node);
}
