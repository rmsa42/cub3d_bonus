/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 10:29:15 by rumachad          #+#    #+#             */
/*   Updated: 2024/06/12 14:20:34 by cacarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void portal_calc(t_player *player, t_v2D old_pos, t_v2D check, t_v2D velocity)
{
	if (fabs(velocity.x) > fabs(velocity.y))
	{
		if (fabs(velocity.y) > 0.01)
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
		if (fabs(velocity.x) > 0.01)
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


void	print_list(t_list *lst);

void	player_move(t_list *objs_lst,t_player *player, char **game_map, t_v2D x, t_v2D y)
{
	t_v2D	velocity;
	t_v2D	new_pos;
	t_v2D	check;
	t_v2D	offset;
	t_v2D	old_pos;
	t_objs	*obj;
	int		i;

	i = 0;
	old_pos = player->pos;
	new_pos = add_vector(x, y);
	new_pos = normalize_vector(new_pos);
	velocity = multiply_vector(new_pos, SPEED);
	offset = multiply_vector(new_pos, SPEED + 0.1);
	check = add_vector(player->pos, offset);
	new_pos = add_vector(player->pos, velocity);
	while(objs_lst)
	{
		obj = (t_objs *)objs_lst->content;
		if (((int)check.x ==  (int)obj->pos.x && (int)check.y ==  (int)obj->pos.y))
			i = 1;
		objs_lst =objs_lst->next;
	}
	if (game_map[(int)check.y][(int)check.x] != '1'
			&& game_map[(int)check.y][(int)check.x] != 'D' && i == 0)
			player->pos = new_pos;
	if (game_map[(int)check.y][(int)check.x] == 'd')
		portal_calc(player, old_pos, check, velocity);
}

void	update_player(t_mlx *mlx, t_player *player, t_map *map)
{
	t_v2D		y_axis;
	t_v2D		x_axis;
	
	// Ball Update
	if (player->shoot == true)
		update_ball(player, &mlx->objs_lst, map->game_map);

	// Player Movement (x, y)
	y_axis = multiply_vector(player->direction, player->movement.y);
	x_axis = multiply_vector(player->plane, player->movement.x);
	player_move(mlx->objs_lst, player, map->game_map, x_axis, y_axis);
	// Player Camera Rotation
	player->direction = add_vector(player->direction, rotate(player->direction, player->angle));
	player->direction = normalize_vector(player->direction);
	player->plane = add_vector(player->plane, rotate(player->plane, player->angle));
	player->plane = normalize_vector(player->plane);
	player->plane = multiply_vector(player->plane, player->fov);
}

