/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 10:02:04 by rumachad          #+#    #+#             */
/*   Updated: 2024/06/14 10:27:25 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	map_parser(char *file_name, t_mlx *mlx)
{
	if (!ft_strnstr(file_name, ".cub", ft_strlen(file_name)))
	{
		print_error("Invalid map extension\n");
		return (1);
	}
	(void)mlx;
	return (0);
}
