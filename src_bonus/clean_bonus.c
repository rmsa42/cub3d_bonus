/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:58:01 by rumachad          #+#    #+#             */
/*   Updated: 2024/06/27 10:11:55 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	print_error(char *str, int status, t_mlx *mlx)
{
	ft_fprintf(STDERR_FILENO, "Error\n");
	perror(str);
	close_game(mlx, status);
}

void	free_config(void *lib, t_sprite *sprite)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (sprite[i].img.img_ptr != NULL)
		{
			mlx_destroy_image(lib, sprite[i].img.img_ptr);
			sprite[i].img.img_ptr = NULL;
		}
		i++;
	}
}

void	close_game(t_mlx *mlx, int status)
{
	if (mlx->sprite->img.img_ptr != NULL)
		sprite_destructor(mlx->lib, mlx->sprite);
	map_destructor(mlx->nbr_maps, mlx->head_map);
	if (mlx->marked_cells != NULL)
		free(mlx->marked_cells);
	obj_destructor(mlx->objs_lst);
	mlx_destructor(mlx->lib, mlx->window);
	exit(status);
}
