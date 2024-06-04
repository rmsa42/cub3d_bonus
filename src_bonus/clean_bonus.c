/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:58:01 by rumachad          #+#    #+#             */
/*   Updated: 2024/06/04 10:57:19 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	close_game(t_mlx *mlx)
{
	int	i;

	i = 0;
	// Sprites
	while (i < 14)
	{
		mlx_destroy_image(mlx->lib, mlx->sprite[i++].img.img_ptr);
		if (i == 4)
			i = 6;
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
	// MLX
	free(mlx->lib);
	exit(0);
}
