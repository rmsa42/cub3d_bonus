/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:49:21 by rumachad          #+#    #+#             */
/*   Updated: 2024/06/27 10:09:48 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	update_state(t_mlx *mlx)
{
	t_player	*player;
	char		**game_map;

	game_map = mlx->map->game_map;
	player = &mlx->player;
	if (player->hp <= 0)
		mlx->game_state = DIED_STATE;
	else if (player->coins == MAX_COINS
		&& mlx->nbr_maps == mlx->iter_map)
		mlx->game_state = WIN_STATE;
	else if (player->coins == MAX_COINS
		&& game_map[(int)player->pos.y][(int)player->pos.x] == 'p')
		mlx->game_state = PORTAL_STATE;
	else
		mlx->game_state = GAME_STATE;
}

void	draw(t_mlx *mlx)
{
	if (mlx->game_state == GAME_STATE)
	{
		ft_grua(mlx);
		draw_minimap(mlx, mlx->objs_lst);
		if (mlx->player.damaged)
			draw_end_game(mlx, DAMAGED);
		if (mlx->player.healed)
		{
			draw_end_game(mlx, HEALED);
			if (mlx->elapsed_time >= 0.10)
				mlx->player.healed = 0;
		}
	}
	else
		end_game(mlx);
}

void	update(t_mlx *mlx)
{
	update_state(mlx);
	if (mlx->game_state == PORTAL_STATE)
	{
		obj_destructor(mlx->objs_lst);
		mlx->objs_lst = NULL;
		free(mlx->marked_cells);
		free_config(mlx->lib, mlx->sprite);
		mlx->map++;
		mlx->iter_map++;
		check_conf(mlx, mlx->map->config_map, mlx->sprite);
		prepare_map(mlx);
	}
	if (mlx->game_state == GAME_STATE)
	{
		update_player(mlx, &mlx->player, mlx->map);
		update_sprites(mlx, &mlx->player, mlx->objs_lst);
		update_animations(mlx);
		enemy_ray(mlx, mlx->objs_lst);
	}
}

int	game_loop(t_mlx *mlx)
{
	update_time(&mlx->current_time);
	mlx->delta = time_passed(&mlx->prev_time, &mlx->current_time);
	mlx->prev_time = mlx->current_time;
	mlx->elapsed_time = time_passed(&mlx->last_time, &mlx->current_time);
	mlx->elapsed_door = time_passed(&mlx->door_time, &mlx->current_time);
	mlx->img = image_buffer(mlx);
	update(mlx);
	draw(mlx);
	mlx_put_image_to_window(mlx->lib, mlx->window,
		mlx->img.img_ptr, 0, 0);
	mlx_destroy_image(mlx->lib, mlx->img.img_ptr);
	return (0);
}
