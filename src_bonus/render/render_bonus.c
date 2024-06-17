/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:49:21 by rumachad          #+#    #+#             */
/*   Updated: 2024/06/17 10:59:02 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_image	new_image(t_mlx *mlx)
{
	t_image	img;

	img.img_ptr = mlx_new_image(mlx->lib, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img_ptr, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	return (img);
}

void minimap_tiles(t_mlx *mlx,int tile_size)
{
	int x;
	int y;
	int i;
	int j;
	int flag;
	i = -1;
	j = -1;
	y = -1;
	while (++y < mlx->map_height) 
	{
		x = -1;
		flag = 0;
		while (++x < (int)ft_strlen(mlx->map.game_map[y])) 
		{
			int color;
			if (mlx->map.game_map[y][x] == '0' && flag == 0)
				color = 0x9c9c9c;
			else if(mlx->map.game_map[y][x] == 'D' || mlx->map.game_map[y][x] == 'd')
				color = 0x0050FF;
			else if (mlx->map.game_map[y][x] == 'X')
				color = 0xFFFFFF;
			else
				color = 0x000000;
			if (mlx->map.game_map[y][x] == '\n')
				flag = 1;
			int tile_x = x * tile_size;
			int tile_y = y * tile_size;
			i = -1;
			while (++i < tile_size) 
			{
				j = -1;
				while (++j < tile_size)
					pixel_put(&mlx->img, tile_x + i, tile_y + j, color);
			}
		}
	}
}

void	map_objs(t_mlx *mlx, t_list *objs_lst, int tile_size, int i, int j)
{
	t_v2D	sprite;
	t_objs		*obj;

	while (objs_lst != NULL)
	{
		obj = (t_objs *)objs_lst->content;
		sprite = multiply_vector(obj->pos, tile_size);
		if (obj->type == ENEMY)
			pixel_put(&mlx->img, sprite.x + i, sprite.y + j, 0xFF0000);
		else
			pixel_put(&mlx->img, sprite.x + i, sprite.y + j, 0xFFFF00);
		objs_lst = objs_lst->next;
	}	
}

void	draw_map_sprites(t_mlx *mlx, t_list *objs_lst, int tile_size)
{
	t_v2D	player;
	t_v2D	ball;
	t_objs	*obj;
	int sprite_size = tile_size / 2;
	int i;
	int	j;
	
	i = -sprite_size;
	player = multiply_vector(mlx->player.pos, tile_size);
	if (mlx->player.shoot == true)
	{
		obj = (t_objs *)mlx->player.ball_node->content;
		ball = multiply_vector(obj->pos, tile_size);
	}
	while (i < sprite_size) 
	{
		j = -sprite_size;
		while (j < sprite_size) 
		{
			objs_lst = mlx->objs_lst;
			map_objs(mlx, objs_lst, tile_size, i , j);
			if (mlx->player.shoot == true)
				pixel_put(&mlx->img, ball.x + i, ball.y + j, 0x0000FF);
			pixel_put(&mlx->img, player.x + i, player.y + j, 0x00FF00);
			j++;
		}
		i++;
	}
}

void draw_minimap(t_mlx *mlx, t_list *objs_lst) 
{
	int minimap_size = 200;
	int tile_size = minimap_size / 36;
	
	minimap_tiles(mlx, tile_size);
	draw_map_sprites(mlx, objs_lst, tile_size);
}

int	render(t_mlx *mlx)
{
	update_time(&mlx->current_time);
	mlx->delta = time_passed(&mlx->prev_time, &mlx->current_time);
	mlx->prev_time = mlx->current_time;
	mlx->img = new_image(mlx);
	mlx->elapsed_time = time_passed(&mlx->last_time, &mlx->current_time);
	mlx->elapsed_door = time_passed(&mlx->door_time, &mlx->current_time);
	update_sprites(mlx, &mlx->player, mlx->objs_lst);
	update_player(mlx, &mlx->player, &mlx->map);
	ft_grua(mlx);
	enemy_ray(mlx, mlx->objs_lst);
	if (mlx->player.hp > 0 && mlx->player.coins < 4)
		draw_minimap(mlx, mlx->objs_lst);
	mlx_put_image_to_window(mlx->lib, mlx->window,
			mlx->img.img_ptr, 0, 0);
	mlx_destroy_image(mlx->lib, mlx->img.img_ptr);
	return (0);
}
