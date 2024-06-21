/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:58:01 by rumachad          #+#    #+#             */
/*   Updated: 2024/06/21 12:18:37 by rumachad         ###   ########.fr       */
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
			mlx_destroy_image(lib, sprite[i].img.img_ptr);
		i++;
	}
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
		else if (obj->type == COLLECT)
			printf("Coin\n");
		else if (obj->type == HP_COLLECT)
			printf("Life\n");
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

void	sprite_destructor(void *lib, t_sprite *sprite)
{
	int	i;

	i = 0;
	while (i < SPRITE_NBR)
	{
		if (sprite[i].img.img_ptr != NULL)
			mlx_destroy_image(lib, sprite[i].img.img_ptr);
		i++;
	}
}

void	map_destructor(t_map *map)
{
	int	i;

	i = 0;
	while (map->config_map[i])
		free(map->config_map[i++]);
	ft_free_dp((void **)map->game_map);
}

void	mlx_destructor(void *lib, void *window)
{
	if (window != NULL)
	{
		mlx_clear_window(lib, window);
		mlx_destroy_window(lib, window);
	}
	if (lib != NULL)
	{
		mlx_destroy_display(lib);
		free(lib);
	}
}

void	close_game(t_mlx *mlx, int status)
{
	if (mlx->sprite->img.img_ptr != NULL)
		sprite_destructor(mlx->lib, mlx->sprite);
	if (mlx->map.game_map != NULL)
		map_destructor(&mlx->map);
	if (mlx->marked_cells != NULL)
		free(mlx->marked_cells);
	obj_destructor(mlx->objs_lst);
	mlx_destructor(mlx->lib, mlx->window);
	exit(status);
}
