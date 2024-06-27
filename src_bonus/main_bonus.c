/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:26:29 by rumachad          #+#    #+#             */
/*   Updated: 2024/06/27 11:09:57 by cacarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	check_conf(t_mlx *mlx, char **conf_map, t_sprite *sprite)
{
	int	k;
	int	*rgb;

	k = -1;
	rgb = (int *)malloc(sizeof(int) * 3);
	if (rgb == NULL)
		return (1);
	ft_memset(rgb, 0, sizeof(int) * 3);
	while (++k < 6)
	{
		if (k >= 0 && k < 4)
			check_element(mlx, &sprite[k], conf_map, k);
		else if (k >= 4)
			check_fc(&sprite[k], &rgb, conf_map, k);
	}
	free(rgb);
	return (0);
}

void	start_game(t_mlx *mlx)
{
	mlx_hook(mlx->window, MotionNotify, PointerMotionMask,
		handle_mouse, mlx);
	mlx_hook(mlx->window, KeyPress, KeyPressMask,
		handle_key_press, mlx);
	mlx_mouse_hook(mlx->window, handle_mouse_press, mlx);
	mlx_hook(mlx->window, KeyRelease, KeyReleaseMask,
		handle_key_release, &mlx->player);
	mlx_mouse_hide(mlx->lib, mlx->window);
	mlx_loop_hook(mlx->lib, game_loop, mlx);
	mlx_loop(mlx->lib);
}

int	main(int argc, char *argv[])
{
	t_mlx	mlx;

	if (argc < 2)
		return (ft_fprintf(STDERR_FILENO, "Invalid nbr arguments\n"), 1);
	mlx.lib = mlx_init();
	if (mlx.lib == NULL)
		print_error("Mlx init failure\n", EXIT_FAILURE, &mlx);
	init_mlx_vars(&mlx, argc);
	if (init_mlx_structs(&mlx))
		print_error("", EXIT_FAILURE, &mlx);
	init_map(&mlx, mlx.nbr_maps, argv);
	init_sprite(&mlx, mlx.map->config_map, mlx.sprite);
	if (prepare_map(&mlx))
		print_error("Invalid Map(Two Players)\n", EXIT_FAILURE, &mlx);
	mlx.window = mlx_new_window(mlx.lib, WIDTH, HEIGHT, "cub3D");
	if (mlx.window == NULL)
		print_error("Mlx window creation failure\n", EXIT_FAILURE, &mlx);
	start_game(&mlx);
	return (0);
}
