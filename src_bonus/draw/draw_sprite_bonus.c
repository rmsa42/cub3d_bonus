/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 20:42:31 by rumachad          #+#    #+#             */
/*   Updated: 2024/06/07 15:43:39 by cacarval         ###   ########.fr       */
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

void	draw_hp(t_mlx *mlx)
{
	t_v2D	scr;
	t_v2D	texture;
	int		color;

	scr.y = HEIGHT - 175;
	int new_size = (int)(SPRITE_SIZE * 2);
	int i;
	i = 0;
	if (mlx->player.hp > 75)
		i = 26;
	else if (mlx->player.hp <= 75 && mlx->player.hp > 50)
		i = 27;
	else if (mlx->player.hp <= 50 && mlx->player.hp > 25)
		i = 28;
	else
		i = 29;
	while (++scr.y < HEIGHT - 175 + new_size) {
		scr.x = 20;
		while (++scr.x < 20 + new_size) {
			texture.x = (int)((scr.x - 20) / 2);
			texture.y = (int)((scr.y - (HEIGHT - 175)) / 2);

			if (texture.x >= 0 && texture.x < SPRITE_SIZE && texture.y >= 0 && texture.y < SPRITE_SIZE) {
				color = pixel_get(&mlx->sprite[i].img, texture.x, texture.y);
				if (color != (int)0xFF00FF) {
					pixel_put(&mlx->img, scr.x, scr.y, color);
				}
			}
		}
	}
}


int	calc_char_anim(t_mlx *mlx)
{
	// static struct timespec last_time;
	// struct timespec current_time;
	// double elapsed_time;
	static int char_anim = 18;
	double chosen_time = 0.10;
	static int i = 0;

	if(mlx->player.shoot == true && i == 0 && mlx->player.anim == true)
	{
		i = 1;
		char_anim = 30;
	}
/* 	if (last_time.tv_sec == 0 && last_time.tv_nsec == 0)
		update_time(&last_time);
	update_time(&current_time);
	elapsed_time = time_passed(&last_time, &current_time); */
	if (mlx->elapsed_time >= chosen_time)
	{
		char_anim++;
		update_time(&mlx->last_time);
	}
	if (char_anim == 26 || char_anim == 38)
	{
		mlx->player.anim = false;
		i = 0;
		char_anim = 18;
	}
	return(char_anim);
}

void	draw_char(t_mlx *mlx, int char_anim)
{
	t_v2D	scr;
	t_v2D	texture;
	int		color;

	scr.y = HEIGHT - 110;
	int new_size = (int)(SPRITE_SIZE * 2);

	while (++scr.y < HEIGHT - 110 + new_size) {
		scr.x = 20;
		while (++scr.x < 20 + new_size) {
			texture.x = (int)((scr.x - 20) / 2);
			texture.y = (int)((scr.y - (HEIGHT - 110)) / 2);

			if (texture.x >= 0 && texture.x < SPRITE_SIZE && texture.y >= 0 && texture.y < SPRITE_SIZE) {
				color = pixel_get(&mlx->sprite[char_anim].img, texture.x, texture.y);
				if (color != (int)0xFF00FF) {
					pixel_put(&mlx->img, scr.x, scr.y, color);
				}
			}
		}
	}
}

void	sprite_loop(t_mlx *mlx)
{
	int		i;
	t_v2D	s_dist;
	t_objs	*objs;
	int		char_anim;
	i = 0;
	objs = mlx->objs;
	while (objs != NULL)
	{
		s_dist = sprite_dist(&mlx->player, objs->pos);
		if (objs->type == ENEMY)
			mlx->spr_index = 13;
		else if (objs->type == KEY)
			mlx->spr_index = 15;
		draw_sprite(s_dist, mlx, &mlx->sprite[mlx->spr_index].img);
		objs = objs->next;
	}
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
