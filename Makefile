# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/18 10:38:51 by rumachad          #+#    #+#              #
#    Updated: 2024/06/27 10:42:33 by cacarval         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

BONUS = cub3D_bonus

SRC_BONUS_PATH = src_bonus/
SRC_PATH = src/
VPATH = $(SRC_BONUS_PATH) $(SRC_BONUS_PATH)render $(SRC_BONUS_PATH)raycasting \
		$(SRC_BONUS_PATH)map $(SRC_BONUS_PATH)vector $(SRC_BONUS_PATH)events \
		$(SRC_BONUS_PATH)parser $(SRC_BONUS_PATH)draw
SRC_BONUS = main_bonus.c \
	game_loop_bonus.c \
	handle_events_bonus.c \
	update_player_bonus.c \
	update_ball_bonus.c \
	update_sprites_bonus.c \
	update_animations_bonus.c \
	raycasting_bonus.c \
	ray_hit_bonus.c \
	enemy_raycast_bonus.c \
	init_sprites_bonus.c \
	init_structs_bonus.c \
	prepare_map_bonus.c \
	v2D_math_bonus.c \
	v2D_utils_bonus.c \
	load_image_bonus.c \
	map_parser_bonus.c \
	create_content_map_bonus.c \
	create_full_map_bonus.c \
	check_elements_bonus.c \
	parser_utils_bonus.c \
	flood_fill_bonus.c \
	draw_bonus.c \
	draw_sprite_bonus.c \
	draw_hud_bonus.c \
	draw_extra_bonus.c \
	draw_minimap_bonus.c \
	sort_sprites.c \
	line_calcs_bonus.c \
	clean_bonus.c \
	destructors_bonus.c \
	common_bonus.c \
	check_objs_bonus.c \
	raycaster_help_bonus.c \
	ball_hits_bonus.c \
	put_tile_bonus.c \
	player_inter_bonus.c
	
	
OBJ_BONUS_PATH = obj_bonus/
OBJ_BONUS_FILES = $(SRC_BONUS:.c=.o)
OBJ_BONUS = $(addprefix $(OBJ_BONUS_PATH), $(OBJ_BONUS_FILES))

CC = cc

MLX_HEADER = -I minilibx
MLX_PATH = minilibx-linux
LIBFT_PATH = libft

HEADER_BONUS = include_bonus
CFLAGS = -Wall -Wextra -Werror -I
MLXFLAGS = -Lminilibx-linux -lmlx -lXext -lX11
LIBFTFLAGS = -Llibft -lft
MATHFLAGS = -lm

all: $(BONUS)

$(BONUS):	$(OBJ_BONUS)
			@make -C $(MLX_PATH) > /dev/null 2>&1
			@echo "$(GREEN)MLX Compiled$(RESET)"
			@make -C $(LIBFT_PATH) > /dev/null
			@echo "$(GREEN)Libft Compiled$(RESET)"
			@$(CC) -o $(BONUS) $(OBJ_BONUS) $(MLXFLAGS) $(LIBFTFLAGS) $(MATHFLAGS)
			@echo "$(GREEN)Cub3d Bonus Compiled$(RESET)"

$(OBJ_BONUS_PATH)%.o: %.c
	@mkdir -p $(OBJ_BONUS_PATH)
	@$(CC) $(CFLAGS) $(HEADER_BONUS) $(MLX_HEADER) -c $< -o $@

val: re
	valgrind --leak-check=full --show-leak-kinds=all --max-stackframe=3850736 ./cub3D_bonus maps/map2.cub

bonus: $(BONUS)

clean:
		@make clean -C $(LIBFT_PATH) > /dev/null
		@make clean -C $(MLX_PATH) > /dev/null 2>&1
		@rm -rf $(OBJ_PATH) $(OBJ_BONUS_PATH) > /dev/null

fclean: clean
		@make fclean -C  $(LIBFT_PATH) > /dev/null
		@rm -f $(NAME) $(BONUS)
		@echo "$(GREEN)Objects cleaned$(RESET)"

re: fclean bonus