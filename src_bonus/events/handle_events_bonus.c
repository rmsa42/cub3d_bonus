/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_events_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/06/11 14:23:13 by cacarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_v2D	rotate(t_v2D vector, int degree)
{
	t_v2D	newV;
	double	angle;
	
	angle = degree * ((double)PI / 180);
	newV.x = (vector.x * cos(angle) - vector.y * sin(angle)) * ROTATION_SPEED;
	newV.y = (vector.x * sin(angle) + vector.y * cos(angle)) * ROTATION_SPEED;
	return (newV);
}

int handle_mouse(int x, int y, t_mlx *mlx)
{
	t_v2D center;
	t_v2D vector;

	center = (t_v2D){WIDTH / 2, HEIGHT / 2};
	if (mlx->player.mouse == false)
	{
		if ((x != WIDTH / 2 || y != HEIGHT / 2) && x < WIDTH/1.25)
		{
			vector = (t_v2D){x - center.x, center.y - y};
			mlx->player.pitch += vector.y;
			if (mlx->player.pitch > 200)
				mlx->player.pitch = 200;
			else if (mlx->player.pitch < -200)
				mlx->player.pitch = -200;
			mlx->player.angle = vector.x * 0.5;
			mlx_mouse_move(mlx->lib, mlx->window, WIDTH / 2, HEIGHT / 2);
		}
		else
			mlx->player.angle = 0;
	}
	return (0);
}


void	shoot_ball(t_mlx *mlx)
{
	t_list	*iterator;
	t_list	*last;
	t_objs	*obj;

	if (mlx->map.game_map[(int)mlx->ball_pos.y][(int)mlx->ball_pos.x] != '1' && mlx->map.game_map[(int)mlx->ball_pos.y][(int)mlx->ball_pos.x] != 'D' )
	{
		iterator = mlx->objs_lst;
		last = iterator;
		while (iterator!= NULL)
		{
			obj = (t_objs *)iterator->content;
			if ((int)mlx->ball_pos.x == (int)obj->pos.x && (int)mlx->ball_pos.y == (int)obj->pos.y)
			{
				if (obj->hp == 0)
				{
					if (last == iterator)
						mlx->objs_lst = mlx->objs_lst->next;
					else if (iterator->next && last)
						last->next = iterator->next;
					else if(iterator->next == NULL)
						last->next = NULL;
					free(iterator->content);
					free(iterator);
					mlx->player.shoot = false;
					iterator = NULL;
					iterator = mlx->objs_lst;
					return ;
				}
				obj->hp--;
				mlx->player.shoot = false;
			}
			last = iterator;
			iterator = iterator->next;
		}
		mlx->ball_pos = add_vector(mlx->ball_pos, multiply_vector(mlx->player.direction, SPEED * 3));
	}
	else
		mlx->player.shoot = false;
}

int	handle_keyPress(int keycode, t_mlx *mlx)
{
	t_player	*player;
	
	player = &mlx->player;
	if (keycode == ESC)
		close_game(mlx);
	else if (keycode == W)
		player->movement.y = 1;
	else if (keycode == S)
		player->movement.y = -1;
	else if (keycode == A)
		player->movement.x = -1;
	else if (keycode == D)
		player->movement.x = 1;
	else if (keycode == LARROW)
		player->angle = -1;
	else if (keycode == RARROW)
		player->angle = 1;
	else if (keycode == E)
		interact_door(mlx->map.game_map, player);
	else if (keycode == Q)
		player->mouse = true;
	else if (keycode == 32 && player->shoot == false)
	{
		mlx->test = 16;
		mlx->ball_pos = add_vector(mlx->player.pos, multiply_vector(mlx->player.direction, 0.5));
		player->shoot = true;
		player->anim = true;
	}
	return (0);
}

int	handle_keyRelease(int keycode, t_player *player)
{
	if (keycode == W || keycode == S)
		player->movement.y = 0;
	else if (keycode == A || keycode == D)
		player->movement.x = 0;
	else if (keycode == LARROW || keycode == RARROW)
		player->angle = 0;
	else if (keycode == Q)
		player->mouse = false;
	return (0);
}
