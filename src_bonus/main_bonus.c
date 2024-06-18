/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/06/18 15:34:00 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "vector2D.h"

int	check_conf(void *lib, char **conf_map, t_sprite *sprite)
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
			if (check_path(conf_map[k] + 2))
				return (-1);
			sprite[k] = xpm_to_image(lib, conf_map[k] + 3);
		}
		else if (k >= 4)
		{
			if (check_rgb(&rgb, conf_map[k] + 2))
				return (-1);
			sprite[k].color = shift_color(rgb);
		}
	}
	free(rgb);
	return (0);
}

int	init_mlx(t_mlx *mlx)
{
	mlx->lib = mlx_init();
	if (mlx->lib == NULL)
		return (1);
	mlx->objs_lst = NULL;
	mlx->marked_cells = NULL;
	mlx->num_marked_cells = 0;
	mlx->side = 0;
	mlx->spr_index = 0;
	mlx->spr_hp_index = 0;
	mlx->spr_coins_index = 0;
	mlx->map_width = 0;
	mlx->map_height = 0;
	mlx->delta = 0;
	mlx->max_coins = 0;
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
	return (0);
}

void	update_state(t_mlx *mlx)
{
	/* printf("%d\n", mlx->max_coins); */
	if (mlx->player.hp <= 0)
		mlx->game_state = DIED_STATE;
	else if (mlx->player.coins == mlx->max_coins)
		mlx->game_state = WIN_STATE;
}

int main(int argc, char *argv[])
{	
	t_mlx	mlx;

	if (init_mlx(&mlx))
		print_error("Mlx init failure\n");
	if (argc > 2)
		print_error("Invalid number of arguments\n");
	map_parser(argv[1], &mlx);

	 // Sprite Init
	init_sprite(mlx.lib, mlx.map.config_map, mlx.sprite);

	prepare_map(&mlx);
	
	mlx.window = mlx_new_window(mlx.lib, WIDTH, HEIGHT, "cub3D");
	if (mlx.window == NULL)
		print_error("Mlx window creation failure\n");
	
	mlx_hook(mlx.window, MotionNotify, PointerMotionMask, handle_mouse, &mlx);
	mlx_hook(mlx.window, KeyPress, KeyPressMask, handle_keyPress, &mlx);
	mlx_mouse_hook(mlx.window, handle_mouse_press, &mlx);
	mlx_hook(mlx.window, KeyRelease, KeyReleaseMask, handle_keyRelease, &mlx.player);
	mlx_mouse_hide(mlx.lib, mlx.window);
	mlx_loop_hook(mlx.lib, game_loop, &mlx);
	mlx_loop(mlx.lib);
	return (0);	
}
