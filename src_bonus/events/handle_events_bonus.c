/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_events_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/06/03 14:52:00 by rumachad         ###   ########.fr       */
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

void portal_calc(t_player *player, t_v2D old_pos, t_v2D check, t_v2D velocity)
{
		if (fabs(velocity.x) > fabs(velocity.y))
		{
			if(fabs(velocity.y) > 0.01)
				player->pos = old_pos;
			else
			{
				if (velocity.x > 0)
					player->pos.x = check.x + 0.5;
				else if (velocity.x < 0)
					player->pos.x = check.x - 0.5;
			}
		}
		else
		{
			if(fabs(velocity.x) > 0.01)
				player->pos = old_pos;
			else
			{
				if (velocity.y > 0)
					player->pos.y = check.y + 0.5;
				else if (velocity.y < 0)
					player->pos.y = check.y - 0.5;

			}
		}
}

void	player_move(t_player *player, char **game_map, t_v2D x, t_v2D y)
{
	t_v2D	velocity;
	t_v2D	new_pos;
	t_v2D	check;
	t_v2D	new_velo;
	t_v2D	old_pos;

	old_pos = player->pos;
	new_pos = add_vector(x, y);
	new_pos = normalize_vector(new_pos);
	velocity = multiply_vector(new_pos, SPEED);
	new_velo = multiply_vector(new_pos, SPEED + 0.1);
	check = add_vector(player->pos, new_velo);
	new_pos = add_vector(player->pos, velocity);
	if (game_map[(int)check.y][(int)check.x] != '1'
		&& game_map[(int)check.y][(int)check.x] != 'D')
		player->pos = new_pos;
	if (game_map[(int)check.y][(int)check.x] == 'd')
		portal_calc(player, old_pos, check, velocity);
}

void	sprite_move(t_player *player, t_v2D *spr_pos)
{
	t_v2D	dir;
	t_v2D	velocity;

	dir.x = player->pos.x - spr_pos->x;
	dir.y = player->pos.y - spr_pos->y;
	dir = normalize_vector(dir);
	velocity = multiply_vector(dir, SPEED * 0.1);
	*spr_pos = add_vector(*spr_pos, velocity);
}

void	update(t_mlx *mlx)
{
	t_player	*player;
	t_tile		tile;
	t_v2D		y_axis;
	t_v2D		x_axis;
	
	// Player Movement (x, y)
	player = &mlx->player;
	tile = get_next_tile(mlx->map.game_map, player);
	if (player->key)
		interact_door(&tile, mlx->map.game_map, &mlx->player);
	y_axis = multiply_vector(player->direction, player->movement.y);
	x_axis = multiply_vector(player->plane, player->movement.x);
	player_move(player, mlx->map.game_map, x_axis, y_axis);
	sprite_move(&mlx->player, &mlx->spr_pos);
	
	// Player Camera Rotation
	player->direction = add_vector(player->direction, rotate(player->direction, player->angle));
	player->direction = normalize_vector(player->direction);
	player->plane = add_vector(player->plane, rotate(player->plane, player->angle));
	player->plane = normalize_vector(player->plane);
	player->plane = multiply_vector(player->plane, player->fov);
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
		player->key = true;
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
	return (0);
}
