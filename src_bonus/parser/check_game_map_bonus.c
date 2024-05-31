/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_game_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:27:25 by jmarinho          #+#    #+#             */
/*   Updated: 2024/05/31 12:46:43 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void    ft_get_rows(t_mlx *mlx)
{
    int i;

    i = -1;
    mlx->map.x = 0;
    if (!mlx->map.game_map)
        return ;
    while (mlx->map.game_map[++i])
        mlx->map.x++;
}

void    ft_get_cols(t_mlx *mlx)
{
    int i;

    i = -1;
    mlx->map.y = 0;
    if (!mlx->map.game_map)
        return ;
    while (mlx->map.game_map[++i])
    {
        if ((int)ft_strlen(mlx->map.game_map[i]) > mlx->map.y)
            mlx->map.y = ft_strlen(mlx->map.game_map[i]);
    }
    mlx->map.y--;//retira o \n da contagem de colunas
}

void    ft_check_invalid_chars(t_mlx *mlx)
{
    int i;
    int k;

    
    i = -1;
    while (mlx->map.game_map[++i])
    {
        k = -1;
        while (mlx->map.game_map[i][++k])
        {
            if (mlx->map.game_map[i][k] != '0' && mlx->map.game_map[i][k] != '1' && mlx->map.game_map[i][k] != 'N' 
                && mlx->map.game_map[i][k] != 'S' && mlx->map.game_map[i][k] != 'E' && mlx->map.game_map[i][k] != 'W'
                    && mlx->map.game_map[i][k] != ' ' && mlx->map.game_map[i][k] != '\t')
                ft_perror("ERROR\nInvalid characters on game map\n", mlx);
        }  
    }
}

/* void    ft_check_walls(t_mlx *mlx)
{
    int i;
    int j;

    i = -1;
    while(mlx->map.game_map[++i])
    {
        j = -1;
        while(mlx->map.game_map[i][++j])
        {
            if (mlx->map.game_map[i][j] == ' ' || mlx->map.game_map[i][j] == '\t')
                j++;
            if (i == 0 || i == mlx->map.x)
                if (mlx->map.game_map[i][j] != '1' || mlx->map.game_map[i][j] != ' ' || mlx->map.game_map[i][j] != '\t')
                    ft_perror("ERROR\nInvalid map (1)\n", mlx);
                else if (mlx->map.game_map[i][0] != '1' || mlx->map.game_map[i][mlx->map.y] != '1')
                    ft_perror("ERROR\nInvalid map (2)\n", mlx);
            if (ft_strlen(mlx->map.game_map[i]) > ft_strlen(mlx->map.game_map[0])
                && mlx->map.game_map[i][j] > ft_strlen(mlx->map.game_map[i]))
                if (mlx->map.game_map[i][j] != '1')
                    ft_perror("ERROR\nInvalid map (3)\n", mlx);
            if (ft_strlen(mlx->map.game_map[i]) > ft_strlen(mlx->map.game_map[mlx->map.x])
                && mlx->map.game_map[i][j] > ft_strlen(mlx->map.game_map[mlx->map.x]))
                if (mlx->map.game_map[i][j] != '1')
                    ft_perror("ERROR\nInvalid map (4)\n", mlx);                  
        }
        
    }
} */

void    ft_check_game_map(t_mlx *mlx)
{   
    #//TODO fazer checkagens ao mapa
    //The map must be closed/surrounded by walls, if not the program must return an error
    //check for invalids chars in map
    //print_map(mlx->map.game_map);
    ft_check_invalid_chars(mlx);
    ft_get_rows(mlx);
    ft_get_cols(mlx);
/*     ft_check_walls(mlx);
 */}
