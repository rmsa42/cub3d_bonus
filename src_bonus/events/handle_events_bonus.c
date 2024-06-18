/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_events_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/06/19 00:44:38 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_v2D	rotate(t_v2D vector, double degree)
{
	t_v2D	newV;
	double	angle;
	
	angle = degree * ((double)PI / 180);
	newV.x = (vector.x * cos(angle) - vector.y * sin(angle));
	newV.y = (vector.x * sin(angle) + vector.y * cos(angle));
	return (newV);
}

int handle_mouse(int x, int y, t_mlx *mlx)
{
	t_v2D center;
	t_v2D vector;

	center = (t_v2D){WIDTH / 2, HEIGHT / 2};
	if (mlx->player.mouse == false)
	{
		if ((x != WIDTH / 2 || y != HEIGHT / 2) && x < WIDTH / 1.25)
		{
			vector = (t_v2D){x - center.x, center.y - y};
			mlx->player.pitch += vector.y;
			if (mlx->player.pitch > 200)
				mlx->player.pitch = 200;
			else if (mlx->player.pitch < -200)
				mlx->player.pitch = -200;
			mlx->player.angle = vector.x * 0.1;
			mlx_mouse_move(mlx->lib, mlx->window, WIDTH / 2, HEIGHT / 2);
		}
		else
			mlx->player.angle = 0;
	}
	return (0);
}

int handle_mouse_press(int button, int x, int y, t_mlx *mlx)
{
	(void)x;
	(void)y;
	if (button == LEFT_CLICK && mlx->player.shoot == false)
		mlx->player.ball_node = init_ball(&mlx->objs_lst, &mlx->player);
	return(0);
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
	else if (keycode == SPACE && player->shoot == false)
		player->ball_node = init_ball(&mlx->objs_lst, &mlx->player);
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
