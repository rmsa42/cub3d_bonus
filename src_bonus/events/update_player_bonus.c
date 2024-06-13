/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 10:29:15 by rumachad          #+#    #+#             */
/*   Updated: 2024/06/13 15:07:56 by cacarval         ###   ########.fr       */
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

t_v2D	get_position(t_player *player, double speed)
{
	t_v2D	velocity;
	t_v2D	new_pos;
	t_v2D	y;
	t_v2D	x;

	y = multiply_vector(player->direction, player->movement.y);
	x = multiply_vector(player->plane, player->movement.x);
	new_pos = add_vector(x, y);
	new_pos = normalize_vector(new_pos);
	velocity = multiply_vector(new_pos, speed);
	new_pos = add_vector(player->pos, velocity);
	return(new_pos);
}

bool	object_check(t_mlx *mlx, t_list *objs_lst, char **game_map, t_v2D check)
{
	t_objs	*obj;
	t_list	*delete;
	bool	i;

	i = false;
	while(objs_lst)
	{
		obj = (t_objs *)objs_lst->content;
		if (((int)check.x ==  (int)obj->pos.x && (int)check.y ==  (int)obj->pos.y))
		{
			if(obj->type == COLLECT && mlx->player.coins < 4)
			{
				delete = objs_lst;
				objs_lst = objs_lst->next;
				elim_obj(&mlx->objs_lst, delete);
				mlx->player.coins++;
				continue ;
			}
			i = true;
		}
		objs_lst = objs_lst->next;
	}
	if (game_map[(int)check.y][(int)check.x] == '1'
			|| game_map[(int)check.y][(int)check.x] == 'D')
			i = true;
	return(i);
}

void	player_move(t_player *player, char **game_map, t_v2D new_pos, t_v2D check)
{
	t_v2D	old_pos;
	t_v2D	velocity;

	old_pos = player->pos;
	velocity = minus_vector(new_pos, player->pos);
	if (game_map[(int)check.y][(int)check.x] == 'd')
	{
		portal_calc(player, old_pos, check, velocity);
		return ;
	}
	player->pos = new_pos;
	
}


void	update_player(t_mlx *mlx, t_player *player, t_map *map)
{
	t_v2D		new_pos;
	t_v2D		check;
	bool		collision;
	// Ball Update
	if (player->shoot == true)
		update_ball(player, &mlx->objs_lst, map->game_map);

	// Player Movement (x, y)
	new_pos = get_position(player, SPEED);
	check = get_position(player, SPEED + 0.1);
	collision = object_check(mlx, mlx->objs_lst, map->game_map, check);
	if (collision == false)
		player_move(player, map->game_map, new_pos, check);

	// Player Camera Rotation
	player->direction = add_vector(player->direction, rotate(player->direction, player->angle));
	player->direction = normalize_vector(player->direction);
	player->plane = add_vector(player->plane, rotate(player->plane, player->angle));
	player->plane = normalize_vector(player->plane);
	player->plane = multiply_vector(player->plane, player->fov);
}

