/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructors_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:32:04 by rumachad          #+#    #+#             */
/*   Updated: 2024/06/27 10:12:01 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

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

void	map_destructor(int nbr_maps, t_map *map)
{
	int	i;
	int	k;

	k = 0;
	while (k < nbr_maps)
	{
		i = 0;
		while (map[k].config_map[i])
		{
			if (map[k].config_map[i])
				free(map[k].config_map[i++]);
		}
		if (map[k].game_map)
			ft_free_dp((void **)map[k].game_map);
		map[k].game_map = NULL;
		k++;
	}
	free(map);
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
