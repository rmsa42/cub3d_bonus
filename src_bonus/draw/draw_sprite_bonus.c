/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 20:42:31 by rumachad          #+#    #+#             */
/*   Updated: 2024/06/08 16:04:38 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_v2D	sprite_dist(t_player *player, t_v2D pos)
{
	t_v2D	spr_vector;
	t_v2D	transform;
	double	inv;
	
	spr_vector.x = pos.x - player->pos.x;
	spr_vector.y = pos.y - player->pos.y;
	inv = 1 / (player->plane.x * player->direction.y
				- player->plane.y * player->direction.x);
	transform.x = inv * (player->direction.y * spr_vector.x
							- player->direction.x * spr_vector.y);
	transform.y = inv * (-player->plane.y * spr_vector.x
							+ player->plane.x * spr_vector.y);
	return (transform);
}

void	draw_sprite(t_v2D transform, t_mlx *mlx, t_image *sprite)
{
	int spriteScreen_x = (int)(WIDTH / 2) * (1 + transform.x / transform.y);
	int spriteHeight = abs((int)(HEIGHT / transform.y));
	
	int drawStartY = (-spriteHeight / 2 + HEIGHT / 2) + mlx->player.pitch;
	if (drawStartY < 0)
		drawStartY = 0;
	int drawEndY = (spriteHeight / 2 + HEIGHT / 2) + mlx->player.pitch;
	if (drawEndY >= HEIGHT)	
		drawEndY = HEIGHT;
	int drawStartX = -spriteHeight / 2 + spriteScreen_x;
	if (drawStartX < 0)
		drawStartX = 0;
	int drawEndX = spriteHeight / 2 + spriteScreen_x;
	if (drawEndX >= WIDTH)
		drawEndX = WIDTH;
	
	for (int stripe = drawStartX; stripe < drawEndX; stripe++)
	{
		int tex_x = (256 * (stripe - (-spriteHeight / 2 + spriteScreen_x)) * SPRITE_SIZE / spriteHeight) / 256;
		if (transform.y > 0 && stripe > 0 && stripe < WIDTH && transform.y < mlx->dist_buffer[stripe])
		{
			for (int y = drawStartY; y < drawEndY; y++)
			{
				int d = y * 256 - HEIGHT * 128 + spriteHeight * 128 - mlx->player.pitch * 256;
				int tex_y = ((d * SPRITE_SIZE) / spriteHeight) / 256;
				
				if (tex_y >= 0 && tex_y < SPRITE_SIZE) {
					int color = pixel_get(sprite, tex_x, tex_y);
					if (color != (int)0xFF00FF)
						pixel_put(&mlx->img, stripe, y, color);
				}
			}
		}
	}
}

t_game_obj	**dist_array(t_lst *lst)
{
	t_game_obj	**dist;
	int			i;

	i = 0;
	dist = malloc(sizeof(t_game_obj *) * (lst_size(lst) + 1));
	if (dist == NULL)
		return (perror("Sprite Malloc"), NULL);
	while (lst != NULL)
	{
		dist[i++] = (t_game_obj *)lst->data;
		lst = lst->next;
	}
	dist[i] = 0;
	return (dist);
}

double	player_obj_dist(t_v2D *pl_pos, t_v2D *spr_pos)
{
	double	dist;
	double	x;
	double	y;

	x = (pl_pos->x - spr_pos->x);
	y = (pl_pos->y - spr_pos->y);
	dist = (x * x) + (y * y);
	return (dist);
}

int	compare_dist(t_v2D *pl_pos, t_game_obj *obj1, t_game_obj *obj2)
{
	double	dist1;
	double	dist2;

	dist1 = player_obj_dist(pl_pos, &obj1->pos);
	dist2 = player_obj_dist(pl_pos, &obj2->pos);
	printf("Dist1: %f\n", dist1);
	printf("Dist2: %f\n", dist2);
	return (dist2 > dist1);
}

void	dist_sort(t_game_obj **dist, t_v2D *pl_pos)
{
	t_game_obj	*temp;
	int			i;
	int			j;

	i = 0;
	while (dist[i] != NULL)
	{
		j = i + 1;
		while (dist[j] != NULL)
		{
			if (compare_dist(pl_pos, dist[i], dist[j]))
			{
				temp = dist[i];
				dist[i] = dist[j];
				dist[j] = temp;
			}
			j++;
		}
		i++;
	}
}

void	update_list(t_lst *union_lst, t_game_obj **dist)
{
	int	i;
	
	i = 0;
	while (union_lst != NULL)
	{
		union_lst->data = dist[i++];
		union_lst = union_lst->next;
	}
	free(dist);
}

void	lst_loop(t_mlx *mlx, t_lst *union_lst)
{
	t_v2D		s_dist;
	t_game_obj	*obj;
	
	s_dist = (t_v2D){0, 0};
	while (union_lst != NULL)
	{
		obj = (t_game_obj *)union_lst->data;
		s_dist = sprite_dist(&mlx->player, obj->pos);
		draw_sprite(s_dist, mlx, &mlx->sprite[13].img);
		union_lst = union_lst->next;
	}
}

void	sprite_loop(t_mlx *mlx)
{
	t_v2D		s_dist;
	t_game_obj	**dist;
	int		char_anim;
	
	s_dist = (t_v2D){0, 0};
	dist = dist_array(mlx->union_list);
	dist_sort(dist, &mlx->player.pos);
	update_list(mlx->union_list, dist);
	lst_loop(mlx, mlx->union_list);
	char_anim = calc_char_anim(mlx);
	draw_char(mlx, char_anim);
	draw_hp(mlx);
	if(mlx->player.shoot == true)
	{
		shoot_ball(mlx);
		s_dist = sprite_dist(&mlx->player, mlx->ball_pos);
		draw_sprite(s_dist, mlx, &mlx->sprite[mlx->test].img);
	}
	// print_vector(mlx->ball_pos);
}
