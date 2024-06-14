/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprites_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 22:38:56 by rumachad          #+#    #+#             */
/*   Updated: 2024/06/13 13:16:46 by cacarval         ###   ########.fr       */
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

void	init_sprite3(void *lib, t_sprite *sprite)
{
	sprite[49] = xpm_to_image(lib, "sprites/sprite/dying5.xpm");
	sprite[50] = xpm_to_image(lib, "sprites/sprite/dying6.xpm");
	sprite[51] = xpm_to_image(lib, "sprites/sprite/dying7.xpm");
	sprite[52] = xpm_to_image(lib, "sprites/coins.xpm");
	sprite[53] = xpm_to_image(lib, "sprites/coins2.xpm");
	sprite[54] = xpm_to_image(lib, "sprites/coins3.xpm");
	sprite[55] = xpm_to_image(lib, "sprites/coins4.xpm");
	sprite[56] = xpm_to_image(lib, "sprites/coins5.xpm");
	sprite[57] = xpm_to_image(lib, "sprites/collec.xpm");
}

void	init_sprite2(void *lib, t_sprite *sprite)
{
	sprite[24] = xpm_to_image(lib, "sprites/sprite/character7.xpm");
	sprite[25] = xpm_to_image(lib, "sprites/sprite/character8.xpm");
	sprite[26] = xpm_to_image(lib, "sprites/sprite/hp.xpm");
	sprite[27] = xpm_to_image(lib, "sprites/sprite/hp2.xpm");
	sprite[28] = xpm_to_image(lib, "sprites/sprite/hp3.xpm");
	sprite[29] = xpm_to_image(lib, "sprites/sprite/hp4.xpm");
	sprite[30] = xpm_to_image(lib, "sprites/sprite/attack.xpm");
	sprite[31] = xpm_to_image(lib, "sprites/sprite/attack1.xpm");
	sprite[32] = xpm_to_image(lib, "sprites/sprite/attack2.xpm");
	sprite[33] = xpm_to_image(lib, "sprites/sprite/attack3.xpm");
	sprite[34] = xpm_to_image(lib, "sprites/sprite/attack4.xpm");
	sprite[35] = xpm_to_image(lib, "sprites/sprite/attack5.xpm");
	sprite[36] = xpm_to_image(lib, "sprites/sprite/attack6.xpm");
	sprite[37] = xpm_to_image(lib, "sprites/sprite/attack7.xpm");
	sprite[38] = xpm_to_image(lib, "sprites/enemy/enemy2.xpm");
	sprite[39] = xpm_to_image(lib, "sprites/enemy/enemy3.xpm");
	sprite[40] = xpm_to_image(lib, "sprites/enemy/enemy4.xpm");
	sprite[41] = xpm_to_image(lib, "sprites/enemy/enemy_down.xpm");
	sprite[42] = xpm_to_image(lib, "sprites/enemy/enemy5.xpm");
	sprite[43] = xpm_to_image(lib, "sprites/enemy/enemy6.xpm");
	sprite[44] = xpm_to_image(lib, "sprites/end_game.xpm");
	sprite[45] = xpm_to_image(lib, "sprites/sprite/dying.xpm");
	sprite[46] = xpm_to_image(lib, "sprites/sprite/dying2.xpm");
	sprite[47] = xpm_to_image(lib, "sprites/sprite/dying3.xpm");
	sprite[48] = xpm_to_image(lib, "sprites/sprite/dying4.xpm");
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
	sprite[16] = xpm_to_image(lib, "sprites/ball.xpm");
	sprite[17] = xpm_to_image(lib, "sprites/ball2.xpm");
	sprite[18] = xpm_to_image(lib, "sprites/character.xpm");
	sprite[19] = xpm_to_image(lib, "sprites/sprite/character2.xpm");
	sprite[20] = xpm_to_image(lib, "sprites/sprite/character3.xpm");
	sprite[21] = xpm_to_image(lib, "sprites/sprite/character4.xpm");
	sprite[22] = xpm_to_image(lib, "sprites/sprite/character5.xpm");
	sprite[23] = xpm_to_image(lib, "sprites/sprite/character6.xpm");
	init_sprite2(lib, sprite);
	init_sprite3(lib, sprite);
}
