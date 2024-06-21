/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/06/21 10:30:02 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "vector2D.h"

int	check_conf(t_mlx *mlx, char **conf_map, t_sprite *sprite)
{
	int	k;
	int	*rgb;

	k = -1;
	rgb = (int *)malloc(sizeof(int) * 3);
	if (rgb == NULL)
		return (0);
	ft_memset(rgb, 0, sizeof(int) * 3);
	while (++k < 6)
	{
		if (k >= 0 && k < 4)
		{
			if (check_path((conf_map[k] + 2) + advance_space(conf_map[k] + 2)))
				return (-1);
			sprite[k] = xpm_to_image(mlx, (conf_map[k] + 2) + advance_space(conf_map[k] + 2));
		}
		else if (k >= 4)
		{
			if (check_rgb(&rgb, conf_map[k] + 1 + advance_space(conf_map[k] + 1)))
				return (-1);
			sprite[k].color = shift_color(rgb);
		}
	}
	free(rgb);
	return (0);
}

void	init_mlx(t_mlx *mlx)
{
	mlx->window = NULL;
	mlx->objs_lst = NULL;
	mlx->marked_cells = NULL;
	mlx->num_marked_cells = 0;
	mlx->side = 0;
	mlx->spr_index = 0;
	mlx->spr_hp_index = 0;
	mlx->spr_character_index = 0;
	mlx->spr_coins_index = 0;
	mlx->delta = 0;
	mlx->elapsed_time = 0;
	mlx->elapsed_door = 0;
	mlx->game_state = GAME_STATE;
	ft_memset(mlx->sprite, 0, sizeof(t_sprite) * SPRITE_NBR);
	ft_memset(&mlx->map, 0, sizeof(t_map));
	ft_memset(&mlx->ray, 0, sizeof(t_ray));
	ft_memset(&mlx->player, 0, sizeof(t_player));
	ft_memset(&mlx->draw, 0, sizeof(t_draw));
	ft_memset(mlx->dist_buffer, 0, sizeof(double) * WIDTH);
	update_time(&mlx->door_time);
	update_time(&mlx->last_time);
	update_time(&mlx->prev_time);
	update_time(&mlx->current_time);
}

int	flood_fill(t_mlx *mlx, t_map map, char **flood_map, t_cell coor)
{
	if (coor.x < 0 || coor.y < 0 || flood_map[coor.y][coor.x] == 32
		|| coor.x >= (int)ft_strlen(flood_map[coor.y])
		|| coor.y > map.height)
	{
		ft_free_dp((void **)flood_map);
		print_error("Invalid Map\n", EXIT_FAILURE, mlx);
	}
	if (flood_map[coor.y][coor.x] == '1')
		return (1);
	flood_map[coor.y][coor.x] = '1';
	flood_fill(mlx, map, flood_map, (t_cell){coor.x + 1, coor.y});
	flood_fill(mlx, map, flood_map, (t_cell){coor.x - 1, coor.y});
	flood_fill(mlx, map, flood_map, (t_cell){coor.x, coor.y + 1});
	flood_fill(mlx, map, flood_map, (t_cell){coor.x, coor.y - 1});
	return (0);
}

int	call_flood_fill(t_mlx *mlx, t_v2D pl_pos)
{
	t_cell	coor;
	char	**flood_map;
	int		i;

	i = -1;
	coor = (t_cell){(int)pl_pos.x, (int)pl_pos.y};
	flood_map = malloc(sizeof(char *) * (mlx->map.height + 1));
	if (flood_map == NULL)
		return (1);
	while (mlx->map.game_map[++i])
		flood_map[i] = ft_strdup(mlx->map.game_map[i]);
	flood_map[i] = 0;
	flood_fill(mlx, mlx->map, flood_map, coor);
	ft_free_dp((void **)flood_map);
	return (0);
}


int main(int argc, char *argv[])
{	
	t_mlx	mlx;

	if (argc > 2)
	{
		ft_fprintf(STDERR_FILENO, "Error\nInvalid arguments\n");
		return (1);
	}
	init_mlx(&mlx);
	mlx.lib = mlx_init();
	if (mlx.lib == NULL)
		print_error("Mlx init failure\n", EXIT_FAILURE, &mlx);

	 // Map Parser
	map_parser(argv[1], &mlx);

	 // Sprite Init
	init_sprite(&mlx, mlx.map.config_map, mlx.sprite);

	prepare_map(&mlx);
	if (call_flood_fill(&mlx, mlx.player.pos))
		print_error("", -1, &mlx);
	
	mlx.window = mlx_new_window(mlx.lib, WIDTH, HEIGHT, "cub3D");
	if (mlx.window == NULL)
		print_error("Mlx window creation failure\n", EXIT_FAILURE, &mlx);

	mlx_hook(mlx.window, MotionNotify, PointerMotionMask, handle_mouse, &mlx);
	mlx_hook(mlx.window, KeyPress, KeyPressMask, handle_keyPress, &mlx);
	mlx_mouse_hook(mlx.window, handle_mouse_press, &mlx);
	mlx_hook(mlx.window, KeyRelease, KeyReleaseMask, handle_keyRelease, &mlx.player);
	/* mlx_mouse_hide(mlx.lib, mlx.window); */
	mlx_loop_hook(mlx.lib, game_loop, &mlx);
	mlx_loop(mlx.lib);
	return (0);	
}
