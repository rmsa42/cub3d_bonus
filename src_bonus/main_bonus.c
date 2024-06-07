/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/06/07 15:34:25 by cacarval         ###   ########.fr       */
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
	mlx->side = 0;
	mlx->spr_index = 0;
	mlx->map_width = 0;
	mlx->map_height = 0;
	ft_memset(mlx->sprite, 0, sizeof(t_sprite) * SPRITE_NBR);
	ft_memset(&mlx->map, 0, sizeof(t_map));
	ft_memset(&mlx->ray, 0, sizeof(t_ray));
	ft_memset(&mlx->player, 0, sizeof(t_player));
	ft_memset(&mlx->draw, 0, sizeof(t_draw));
	ft_memset(mlx->dist_buffer, 0, sizeof(double) * WIDTH);
	ft_memset(&mlx->last_time, 0, sizeof(struct timespec));
	return (0);
}

int handle_mouse_press(int button, int x, int y, t_mlx *mlx)
{
	(void)x;
	(void)y;
	if (button == 1 && mlx->player.shoot == false)
	{
		mlx->test = 16;
		mlx->ball_pos = add_vector(mlx->player.pos, multiply_vector(mlx->player.direction, 0.5));
		mlx->player.shoot = true;
	}
	return(0);
}

int main(int argc, char *argv[])
{	
	t_mlx	mlx;

	// MLX Init
	init_mlx(&mlx);
	
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
	mlx_mouse_hook(mlx.window, handle_mouse_press, &mlx);
	mlx_hook(mlx.window, KeyRelease, KeyReleaseMask, handle_keyRelease, &mlx.player);
	mlx_mouse_hide(mlx.lib, mlx.window);
	mlx_loop_hook(mlx.lib, render, &mlx);
	mlx_loop(mlx.lib);
	
	(void)argc;
	return (0);	
}
