/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprites_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 22:38:56 by rumachad          #+#    #+#             */
/*   Updated: 2024/06/21 11:02:00 by cacarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_sprite	xpm_to_image(t_mlx *mlx, char *texture)
{
	t_sprite	sprite;
	t_image		img;

	img.img_ptr = mlx_xpm_file_to_image(mlx->lib, texture,
						&sprite.width, &sprite.height);
	if (img.img_ptr == NULL)
		print_error("Invalid Sprite\n", EXIT_FAILURE, mlx);
	img.addr = mlx_get_data_addr(img.img_ptr, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	if (img.addr == NULL)
		print_error("Invalid Sprite address\n", EXIT_FAILURE, mlx);
	sprite.img = img;
	return (sprite);
}

void	init_sprite3(t_mlx *mlx, t_sprite *sprite)
{
	sprite[49] = xpm_to_image(mlx, "sprites/sprite/dying5.xpm");
	sprite[50] = xpm_to_image(mlx, "sprites/sprite/dying6.xpm");
	sprite[51] = xpm_to_image(mlx, "sprites/sprite/dying7.xpm");
	sprite[52] = xpm_to_image(mlx, "sprites/coins.xpm");
	sprite[53] = xpm_to_image(mlx, "sprites/coins2.xpm");
	sprite[54] = xpm_to_image(mlx, "sprites/coins3.xpm");
	sprite[55] = xpm_to_image(mlx, "sprites/coins4.xpm");
	sprite[56] = xpm_to_image(mlx, "sprites/coins5.xpm");
	sprite[57] = xpm_to_image(mlx, "sprites/collec.xpm");
	sprite[58] = xpm_to_image(mlx, "sprites/win_game.xpm");
	sprite[59] = xpm_to_image(mlx, "sprites/hp_collect1.xpm");
	sprite[60] = xpm_to_image(mlx, "sprites/end_door/end_door.xpm");
	sprite[61] = xpm_to_image(mlx, "sprites/end_door/end_door1.xpm");
	sprite[62] = xpm_to_image(mlx, "sprites/end_door/end_door2.xpm");
}

void	init_sprite2(t_mlx *mlx, t_sprite *sprite)
{
	sprite[24] = xpm_to_image(mlx, "sprites/sprite/character7.xpm");
	sprite[25] = xpm_to_image(mlx, "sprites/sprite/character8.xpm");
	sprite[26] = xpm_to_image(mlx, "sprites/sprite/hp.xpm");
	sprite[27] = xpm_to_image(mlx, "sprites/sprite/hp2.xpm");
	sprite[28] = xpm_to_image(mlx, "sprites/sprite/hp3.xpm");
	sprite[29] = xpm_to_image(mlx, "sprites/sprite/hp4.xpm");
	sprite[30] = xpm_to_image(mlx, "sprites/sprite/attack.xpm");
	sprite[31] = xpm_to_image(mlx, "sprites/sprite/attack1.xpm");
	sprite[32] = xpm_to_image(mlx, "sprites/sprite/attack2.xpm");
	sprite[33] = xpm_to_image(mlx, "sprites/sprite/attack3.xpm");
	sprite[34] = xpm_to_image(mlx, "sprites/sprite/attack4.xpm");
	sprite[35] = xpm_to_image(mlx, "sprites/sprite/attack5.xpm");
	sprite[36] = xpm_to_image(mlx, "sprites/sprite/attack6.xpm");
	sprite[37] = xpm_to_image(mlx, "sprites/sprite/attack7.xpm");
	sprite[38] = xpm_to_image(mlx, "sprites/enemy/enemy2.xpm");
	sprite[39] = xpm_to_image(mlx, "sprites/enemy/enemy3.xpm");
	sprite[40] = xpm_to_image(mlx, "sprites/enemy/enemy4.xpm");
	sprite[41] = xpm_to_image(mlx, "sprites/enemy/enemy_down.xpm");
	sprite[42] = xpm_to_image(mlx, "sprites/enemy/enemy5.xpm");
	sprite[43] = xpm_to_image(mlx, "sprites/enemy/enemy6.xpm");
	sprite[44] = xpm_to_image(mlx, "sprites/end_game.xpm");
	sprite[45] = xpm_to_image(mlx, "sprites/sprite/dying.xpm");
	sprite[46] = xpm_to_image(mlx, "sprites/sprite/dying2.xpm");
	sprite[47] = xpm_to_image(mlx, "sprites/sprite/dying3.xpm");
	sprite[48] = xpm_to_image(mlx, "sprites/sprite/dying4.xpm");
}

void	init_sprite(t_mlx *mlx, char **conf_map, t_sprite *sprite)
{
	if (check_conf(mlx, conf_map, sprite) == -1)
		print_error("Can't Load Sprites\n", EXIT_FAILURE, mlx);
	sprite[6] = xpm_to_image(mlx, "sprites/door.xpm");
	sprite[7] = xpm_to_image(mlx, "sprites/open.xpm");
	sprite[8] = xpm_to_image(mlx, "sprites/open2.xpm");
	sprite[9] = xpm_to_image(mlx, "sprites/open3.xpm");
	sprite[10] = xpm_to_image(mlx, "sprites/open4.xpm");
	sprite[11] = xpm_to_image(mlx, "sprites/open5.xpm");
	sprite[12] = xpm_to_image(mlx, "sprites/open6.xpm");
	sprite[13] = xpm_to_image(mlx, "sprites/barrel.xpm");
	sprite[14] = xpm_to_image(mlx, "sprites/staff.xpm");
	sprite[15] = xpm_to_image(mlx, "sprites/key.xpm");
	sprite[16] = xpm_to_image(mlx, "sprites/ball.xpm");
	sprite[17] = xpm_to_image(mlx, "sprites/ball2.xpm");
	sprite[18] = xpm_to_image(mlx, "sprites/character.xpm");
	sprite[19] = xpm_to_image(mlx, "sprites/sprite/character2.xpm");
	sprite[20] = xpm_to_image(mlx, "sprites/sprite/character3.xpm");
	sprite[21] = xpm_to_image(mlx, "sprites/sprite/character4.xpm");
	sprite[22] = xpm_to_image(mlx, "sprites/sprite/character5.xpm");
	sprite[23] = xpm_to_image(mlx, "sprites/sprite/character6.xpm");
	init_sprite2(mlx, sprite);
	init_sprite3(mlx, sprite);
}
