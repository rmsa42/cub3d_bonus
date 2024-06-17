/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:58:01 by rumachad          #+#    #+#             */
/*   Updated: 2024/06/17 12:43:34 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	print_error(char *str)
{
	ft_fprintf(STDERR_FILENO, "Error\n%s", str);
}

void	print_list(t_list *lst)
{
	t_objs	*obj;
	
	while (lst != NULL)
	{
		obj = (t_objs *)lst->content;
		if (obj->type == ENEMY)
			printf("Enemy\n");
		else if (obj->type == BALL)
			printf("Ball\n");
		else
			printf("Sprite\n");
		lst = lst->next;
	}
}

void	obj_destructor(t_list *lst)
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
	while (mlx->map.config_map[i])
		free(mlx->map.config_map[i++]);
	ft_free_dp((void **)mlx->map.game_map);
	free(mlx->marked_cells);
	 // Objs
	obj_destructor(mlx->objs_lst);
	 // MLX
	free(mlx->lib);
	exit(0);
}
