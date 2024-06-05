/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 20:42:31 by rumachad          #+#    #+#             */
/*   Updated: 2024/06/05 13:38:42 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_v2D	trans_calc(t_player *player, t_objs *obj)
{
	t_v2D	spr_vector;
	t_v2D	transform;
	double	inv;
	
	spr_vector.x = obj->pos.x - player->pos.x;
	spr_vector.y = obj->pos.y - player->pos.y;
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

double	*dist_array(t_player *player, t_objs *objs, int nbr_sprites)
{
	int		i;
	double	*dist;
	t_v2D	vector;

	i = 0;
	dist = malloc(sizeof(double) * nbr_sprites);
	if (dist == NULL)
		return (perror("Sprite Malloc"), NULL);
	while (i < nbr_sprites)
	{
		vector = (t_v2D){player->pos.x - objs[i].pos.x,
			player->pos.y - objs->pos.y};
		dist[i++] = length_vector(vector);
	}
	return (dist);
}

void	sprite_sort(t_objs *objs, double *dist, int nbr_sprites)
{
	int		i;
	int		j;
	t_objs	temp;

	i = 0;
	while (i < nbr_sprites - 1)
	{
		j = i + 1;
		while (j < nbr_sprites)
		{
			if (dist[i] < dist[j])
			{
				temp = objs[i];
				objs[i] = objs[j];
				objs[j] = temp;
			}
			j++;
		}
		i++;
	}
	free(dist);
}

void	draw_staff(t_mlx *mlx)
{
	t_v2D	scr;
	t_v2D	texture;
	t_image	*img;
	int		color;

	img = &mlx->sprite[14].img;
	scr.y = 200;
	while (++scr.y < HEIGHT)
	{
		scr.x = 200;
		while (++scr.x < WIDTH)
		{
			texture.x = (scr.x - 200) * 64 / WIDTH;
			texture.y = (scr.y - 200) * 64 / HEIGHT;
			color = pixel_get(&mlx->sprite[14].img, texture.x, texture.y);
			if (color != (int)0xFF00FF)
				pixel_put(&mlx->img, scr.x, scr.y, color);
		}
	}
}

void	sprite_loop(t_mlx *mlx)
{
	int		i;
	/* double	*dist; */
	t_v2D	transform;
	t_objs	*objs;

	i = 0;
	objs = mlx->objs;
	while (objs != NULL)
	{
		/* dist = dist_array(&mlx->player, mlx->objs, mlx->nbr_sprites);
		sprite_sort(mlx->objs, dist, mlx->nbr_sprites); */
		transform = trans_calc(&mlx->player, objs);
		if (objs->type == ENEMY)
			mlx->spr_index = 13;
		else if (objs->type == KEY)
			mlx->spr_index = 15;
		draw_sprite(transform, mlx, &mlx->sprite[mlx->spr_index].img);
		objs = objs->next;
	}
	draw_staff(mlx);
}
