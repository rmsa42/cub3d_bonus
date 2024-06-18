/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:49:21 by rumachad          #+#    #+#             */
/*   Updated: 2024/06/18 15:26:55 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	draw(t_mlx *mlx)
{
	if (mlx->game_state == GAME_STATE)
	{
		ft_grua(mlx);
		draw_minimap(mlx, mlx->objs_lst);
	}
	else
		end_game(mlx);
}

void	update(t_mlx *mlx)
{
	update_state(mlx);
	if (mlx->game_state == GAME_STATE)
	{
		update_player(mlx, &mlx->player, &mlx->map);
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