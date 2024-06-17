/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:01:29 by rumachad          #+#    #+#             */
/*   Updated: 2024/06/17 11:42:56 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	create_config_map(t_map *map, char **full_map)
{
	int		i;
	int		counter;
	char	*trimed_line;

	i = 0;
	counter = 0;
	trimed_line = NULL;
	while (counter < 6)
	{
		trimed_line = ft_strtrim(full_map[i], " 	\n");
		if (!trimed_line)
			return (-1);
		else if (!ft_strlen(trimed_line))
			i++;
		else
		{
			map->config_map[counter++] = ft_strdup(trimed_line);
			i++;
		}
		free(trimed_line);
	}
	return (i);
}

int	begining_of_map(char *line, char *set)
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
				return (1);
			k++;	
		}
		i++;
	}
	return (0);
}

int	create_content_map(t_map *map, char **full_map, int after, int len)
{
	int		i;
	int		j;
	char	*trimed_line;

	i = after;
	while (full_map[i])
	{
		if (begining_of_map(full_map[i], "01eCdDNESO"))
			break ;
		i++;
	}
	j = 0;
	trimed_line = NULL;
	map->game_map = malloc(sizeof(char *) * (len - after + 1));
	while (full_map[i])
	{
		trimed_line = ft_strtrim(full_map[i], "\n");
		if (!trimed_line)
			return (-1);
		else
		{
			map->game_map[j++] = ft_strdup(trimed_line);
			i++;
		}
		free(trimed_line);
	}
	map->game_map[j] = 0;
	return (j);
}
