/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 10:02:04 by rumachad          #+#    #+#             */
/*   Updated: 2024/06/17 13:10:51 by cacarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	map_nbr_lines(int fd)
{
	int		i;
	char	*line;

	i = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		i++;
		free(line);
		line = get_next_line(fd);
	}
	return (i);
}

char	**cpy_map(int fd, int len)
{
	char	**map;
	char	*line;
	int		i;

	map = malloc(sizeof(char *) * (len + 1));
	if (map == NULL)
		return (NULL);
	i = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		map[i++] = ft_strdup(line);
		free(line);
		line = get_next_line(fd);
	}
	map[i] = 0;
	return (map);
}

void	check_config_map2(t_mlx *mlx, char *dir, int pos)
{
	char *swap;
	int i;

	i = -1;
	while(mlx->map.config_map[++i])
	{
		if(ft_strncmp(mlx->map.config_map[i], dir, ft_strlen(dir)) == 0)
		{
			swap = mlx->map.config_map[pos];
			mlx->map.config_map[pos] = mlx->map.config_map[i];
			mlx->map.config_map[i] = swap;
			return ;
		}
	}
	print_error("Invalid Configurations");
}

void	check_config_map(t_mlx *mlx)
{
	int i;

	i = -1;
	check_config_map2(mlx, "NO ", 0);
	check_config_map2(mlx, "SO ", 1);
	check_config_map2(mlx, "WE ", 2);
	check_config_map2(mlx, "EA ", 3);
	check_config_map2(mlx, "F ", 4);
	check_config_map2(mlx, "C ", 5);
	
}

int	map_parser(char *map_name, t_mlx *mlx)
{
	int		fd;
	int		nbr_lines;
	char	**full_map;
	int		config_lines;
	
	fd = 0;
	if (!ft_strnstr(map_name, ".cub", ft_strlen(map_name)))
	{
		print_error("Invalid map extension\n");
		return (1);
	}
	fd = open(map_name, O_RDONLY);
	nbr_lines = map_nbr_lines(fd);
	close(fd);
	fd = open(map_name, O_RDONLY);
	full_map = cpy_map(fd, nbr_lines);
	close(fd);
	config_lines = create_config_map(&mlx->map, full_map);
	if (config_lines == -1)
	{
		print_error("Invalid map elements\n");
		return (1);
	}
	check_config_map(mlx);
	mlx->map.height = create_content_map(&mlx->map, full_map, config_lines, nbr_lines);
	ft_free_dp((void **)full_map);
	return (0);
}
