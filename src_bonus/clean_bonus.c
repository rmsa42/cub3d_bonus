/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:58:01 by rumachad          #+#    #+#             */
/*   Updated: 2024/06/05 14:16:22 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	free_objs_list(t_objs *objs)
{
	t_objs	*temp;

	while (objs != NULL)
	{
		temp = objs;
		objs = objs->next;
		free(temp);
	}
}

void	close_game(t_mlx *mlx)
{
	int	i;

	i = 0;
	// Sprites
	while (i < SPRITE_NBR)
	{
		if (mlx->sprite[i].img.img_ptr != NULL)
			mlx_destroy_image(mlx->lib, mlx->sprite[i].img.img_ptr);
		i++;
	}
	// Window
	mlx_clear_window(mlx->lib, mlx->window);
	mlx_destroy_window(mlx->lib, mlx->window);
	mlx_destroy_display(mlx->lib);
	// Map
	i = 0;
	while (i < 6)
		free(mlx->map.config_map[i++]);
	ft_free_dp((void **)mlx->map.game_map);
	// Objs
	free_objs_list(mlx->objs);
	// MLX
	free(mlx->lib);
	exit(0);
}
