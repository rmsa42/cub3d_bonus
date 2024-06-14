/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 20:34:30 by rumachad          #+#    #+#             */
/*   Updated: 2024/06/14 15:53:31 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	color(int nbr)
{
	if (nbr >= 0 && nbr <= 255)
		return (1);
	return (0);
}

int	advance_space(char *line)
{
	int	i;

	i = 0;
	while (line[i] == 32)
		i++;
	return (i);
}

void	print_map(char **map)
{
	int i = 0;

	while (map[i])
		printf("%s\n", map[i++]);
}

int	shift_color(int *rgb)
{
	int	color;
	
	color = (rgb[0] << 16 | rgb[1] << 8
		| rgb[2]);
	return (color);
}
