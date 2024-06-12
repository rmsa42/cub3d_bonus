/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:58:01 by rumachad          #+#    #+#             */
/*   Updated: 2024/06/12 12:51:15 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	free_list(t_list *lst)
{
	t_list	*temp;

	while (lst != NULL)
	{
		temp = lst;
		lst = lst->next;
		free(temp->content);
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
	free(mlx->marked_cells);
	// Objs
	free_list(mlx->objs_lst);
	// MLX
	free(mlx->lib);
	exit(0);
}
