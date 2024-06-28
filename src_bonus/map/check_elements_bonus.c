/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elements_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:57:17 by rumachad          #+#    #+#             */
/*   Updated: 2024/06/28 15:31:30 by rumachad         ###   ########.fr       */
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
		while (rgb[i][j])
			if (ft_isdigit(rgb[i][j++]) == 0)
				return (-1);
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

int	check_element(t_mlx *mlx, t_sprite *sprite, char *conf_map)
{
	if (check_path((conf_map + 2) + advance_space(conf_map + 2)))
		return (1);
	*sprite = xpm_to_image(mlx, (conf_map + 2)
			+ advance_space(conf_map + 2));
	return (0);
}

int	check_fc(t_sprite *sprite, int **rgb, char *conf_map)
{
	if (check_rgb(rgb, conf_map + 1 + advance_space(conf_map + 1)))
		return (1);
	(*sprite).color = shift_color(*rgb);
	return (0);
}
