/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprites_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 22:38:56 by rumachad          #+#    #+#             */
/*   Updated: 2024/06/05 10:53:44 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	get_sprite_img(t_image *img)
{
	img->addr = mlx_get_data_addr(img->img_ptr, &img->bits_per_pixel,
			&img->line_length, &img->endian);
}

t_sprite	xpm_to_image(void *lib, char *texture)
{
	t_sprite	sprite;
	
	sprite.img.img_ptr = mlx_xpm_file_to_image(lib, texture,
						&sprite.width, &sprite.height);
	assert(sprite.img.img_ptr != NULL);
	get_sprite_img(&sprite.img);
	return (sprite);
}

void	init_sprite(void *lib, char **conf_map, t_sprite *sprite)
{
	if (check_conf(lib, conf_map, sprite) == -1)
		ft_fprintf(STDERR_FILENO, "Error\n");
	sprite[6] = xpm_to_image(lib, "sprites/door.xpm");
	sprite[7] = xpm_to_image(lib, "sprites/open.xpm");
	sprite[8] = xpm_to_image(lib, "sprites/open2.xpm");
	sprite[9] = xpm_to_image(lib, "sprites/open3.xpm");
	sprite[10] = xpm_to_image(lib, "sprites/open4.xpm");
	sprite[11] = xpm_to_image(lib, "sprites/open5.xpm");
	sprite[12] = xpm_to_image(lib, "sprites/open6.xpm");
	sprite[13] = xpm_to_image(lib, "sprites/barrel.xpm");
	sprite[14] = xpm_to_image(lib, "sprites/staff.xpm");
	sprite[15] = xpm_to_image(lib, "sprites/key.xpm");
}
