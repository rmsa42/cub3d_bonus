/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_content_map_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:01:29 by rumachad          #+#    #+#             */
/*   Updated: 2024/07/04 11:50:07 by cacarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

char	*begining_of_map(char *line, char *set)
{
	int	i;
	int	k;

	i = 0;
	while (line[i])
	{
		k = 0;
		while (set[k])
		{
			if (line[i] == set[k])
				return (&line[i]);
			k++;
		}
		i++;
	}
	return (NULL);
}

int	get_game_map(t_map *map, char **full_map, int i)
{
	char	*trimed_line;
	int		j;

	j = 0;
	trimed_line = NULL;
	while (full_map[i])
	{
		trimed_line = ft_strtrim(full_map[i], "\n");
		if (!trimed_line)
			return (-1);
		else
		{
			map->game_map[j] = ft_strdup(trimed_line);
			if ((int)ft_strlen(map->game_map[j]) > map->width)
				map->width = ft_strlen(map->game_map[j]);
			i++;
			j++;
		}
		free(trimed_line);
	}
	map->game_map[j] = 0;
	return (j);
}

int	create_content_map(t_map *map, char **full_map, int after, int len)
{
	int		i;
	int		j;

	i = after;
	while (full_map[i])
	{
		if (begining_of_map(full_map[i], "01eCdDNESO"))
			break ;
		i++;
	}
	j = 0;
	map->game_map = malloc(sizeof(char *) * (len - after + 1));
	j = get_game_map(map, full_map, i);
	return (j);
}
