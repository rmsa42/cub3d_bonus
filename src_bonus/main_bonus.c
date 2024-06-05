/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/06/05 14:32:24 by rumachad         ###   ########.fr       */
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
	while (++k < 6)
	{
		if (k >= 0 && k < 4)
		{
			if (check_path(conf_map[k]))
				return (-1);
			sprite[k] = xpm_to_image(lib, conf_map[k]);
		}
		else if (k >= 4)
		{
			if (check_rgb(&rgb, conf_map[k]))
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
	{
		perror("MLX Error\n");
		return (-1);
	}
	
	mlx->objs = NULL;
	mlx->num_marked_cells = 0;
	if (mlx->objs == NULL)
		return (-1);
	ft_memset(mlx->sprite, 0, sizeof(t_sprite) * SPRITE_NBR);
	return (0);
}

int main(int argc, char *argv[])
{	
	t_mlx	mlx;

	// MLX Init
	init_mlx(&mlx);
	ft_memset(&mlx.map, 0, sizeof(t_map));
	// Map init / Parser
	ft_check_b4_init(argc, argv, &mlx);
	
	// Sprite Init
	init_sprite(mlx.lib, mlx.map.config_map, mlx.sprite);
	
	// Create Window
	mlx.window = mlx_new_window(mlx.lib, WIDTH, HEIGHT, "cub3D");
	assert(mlx.window != NULL);

	prepare_map(&mlx);
	
	mlx_hook(mlx.window, MotionNotify, PointerMotionMask, handle_mouse, &mlx);
	mlx_hook(mlx.window, KeyPress, KeyPressMask, handle_keyPress, &mlx);
	mlx_hook(mlx.window, KeyRelease, KeyReleaseMask, handle_keyRelease, &mlx.player);
	/* mlx_mouse_hide(mlx.lib, mlx.window); */
	mlx_loop_hook(mlx.lib, render, &mlx);
	mlx_loop(mlx.lib);
	
	(void)argc;
	return (0);	
}
