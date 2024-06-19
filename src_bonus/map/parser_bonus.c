/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:57:17 by rumachad          #+#    #+#             */
/*   Updated: 2024/06/19 11:38:50 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	check_rgb(int **c, char *line)
{
	char	**rgb;
	int		i;
	int		ele_color;
	int		j;

	i = 0;
	rgb = ft_split(line, ',');
	while (rgb[i])
	{
		j = 0;
		while(rgb[i][j])
			if(ft_isdigit(rgb[i][j++]) == 0)
				return(-1);
		ele_color = ft_atoi(rgb[i]);
		if (color(ele_color))
			c[0][i] = ele_color;
		else
			break ;
		i++;
	}
	ft_free_dp((void **)rgb);
	if (i != 3)
		return (-1);
	return (0);
}

int	check_path(char *line)
{
	int	fd;

	line += advance_space(line);
	fd = open(line, O_RDONLY);
	if (fd == -1)
		return (-1);
	close(fd);
	line += 1;
	if (ft_strncmp(ft_strchr(line, '.'), ".xpm", 5))
		return (-1);
	return (0);
}

int	check_row(char *line)
{
	int	len;

	len = ft_strlen(line);
	if ((line[0] != '1' || line[len] != '1'))
		return (-1);
	return (0);
}

int	check_first_row(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == '1')
		i++;
	if (line[i] == '\0')
		return (0);
	return (-1);
}
