/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/05/29 12:43:07 by cacarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "vector2D.h"

t_player	init_player(double x, double y, char tile)
{
	t_player	player;
	int			dir;

	player.pitch = 0;
	dir = 1;
	player.pos = (t_v2D){x, y};
	if (tile == 'N')
		player.direction = (t_v2D){0, -dir};
	else if (tile == 'S')
		player.direction = (t_v2D){0, dir};
	else if (tile == 'W')
		player.direction = (t_v2D){-dir, 0};
	else if (tile == 'E')
		player.direction = (t_v2D){dir, 0};
	player.movement = (t_v2D){0, 0};
	player.plane = perp_vector(player.direction);
	player.angle = 0.1;
	player.fov = (double)FOV / 90;
	player.open_door = false;
	return (player);
}

int	shift_color(int *rgb)
{
	int	color;
	
	color = (rgb[0] << 16 | rgb[1] << 8
		| rgb[2]);
	return (color);
}

int	check_map(t_mlx *mlx, char **conf_map)
{
	int	i;
	int	k;
	int	*rgb;

	k = 0;
	i = 0;
	rgb = (int *)malloc(sizeof(int) * 3);
	if (rgb == NULL)
		return (0);
	while (conf_map[i])
	{
		k = check_element(conf_map[i]);
		if (k >= 0 && k < 4)
		{
			if (check_path(conf_map[i] + 2))
				return (-1);
			mlx->sprite[k] = xpm_to_image(mlx, conf_map[i] + 3);
		}
		else if (k >= 4)
		{
			if (check_rgb(&rgb, conf_map[i] + 1))
				return (-1);
			mlx->sprite[k].color = shift_color(rgb);
		}
		i++;
	}
	free(rgb);
	return (0);
}

char **teste(char **map)
{
	char	**conf_map;

	conf_map = (char **)malloc(sizeof(char *) * 7);
	for (int i = 0; i < 6; i++)
	{
		conf_map[i] = map[i];
	}
	conf_map[6] = 0;
	return (conf_map);
}

int handle_mouse(int x, int y, t_mlx *mlx)
{
    t_v2D center;
    t_v2D vector;

    center = (t_v2D){WIDTH / 2, HEIGHT / 2};
    if ((x != WIDTH / 2 || y != HEIGHT / 2) && x < WIDTH/1.25)
    {
        vector = (t_v2D){x - center.x, center.y - y};
        mlx->player.pitch += vector.y;
        if (mlx->player.pitch > 200)
            mlx->player.pitch = 200;
        else if (mlx->player.pitch < -200)
            mlx->player.pitch = -200;
        mlx->player.angle = vector.x;
        mlx_mouse_move(mlx->lib, mlx->window, WIDTH / 2, HEIGHT / 2);
    }
    else
        mlx->player.angle = 0;
    return (0);
}

int main(int argc, char *argv[])
{	
	t_mlx	mlx;
	
	mlx.lib = mlx_init();
	assert(mlx.lib != NULL);
	
	/* mlx = ft_check_b4_init(argc, argv, &mlx); */
	
	// Map init / Parser / Sprite Init
	mlx.sprite[6] = xpm_to_image(&mlx, "sprites/door.xpm");
	mlx.sprite[7] = xpm_to_image(&mlx, "sprites/open.xpm");
	mlx.sprite[8] = xpm_to_image(&mlx, "sprites/open2.xpm");
	mlx.sprite[9] = xpm_to_image(&mlx, "sprites/open3.xpm");
	mlx.sprite[10] = xpm_to_image(&mlx, "sprites/open4.xpm");
	mlx.sprite[11] = xpm_to_image(&mlx, "sprites/open5.xpm");
	mlx.sprite[12] = xpm_to_image(&mlx, "sprites/open6.xpm");
	mlx.map = init_map(argv[1]);
	mlx.map.config_map = teste(mlx.map.game_map);
	
	if (check_map(&mlx, mlx.map.config_map))
		return (printf("Check Error\n"), -1);
	
	// Create Window
	mlx.window = mlx_new_window(mlx.lib, WIDTH, HEIGHT, "cub3D");
	assert(mlx.window != NULL);
	
	map_draw(&mlx);

	mlx_hook(mlx.window, 6, PointerMotionMask, handle_mouse, &mlx);
	mlx_hook(mlx.window, KeyPress, KeyPressMask, handle_keyPress, &mlx);
	mlx_hook(mlx.window, KeyRelease, KeyReleaseMask, handle_keyRelease, &mlx.player);
	mlx_mouse_hide(mlx.lib, mlx.window);
	mlx_loop_hook(mlx.lib, render, &mlx);
	mlx_loop(mlx.lib);
	
	(void)argc;
	return (0);	
}
