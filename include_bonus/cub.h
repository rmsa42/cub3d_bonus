/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/06/20 10:27:58 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include "vector2D.h"
# include "sprite_enum.h"
# include <stdbool.h>
# include <time.h>

# define ESC 65307
# define W 119
# define A 97
# define S 115
# define D 100
# define E 101
# define Q 113
# define SPACE 32
# define LEFT_CLICK 1
# define LARROW 65361
# define RARROW 65363

# define HEIGHT 600
# define WIDTH 800
# define FOV 90
# define SPRITE_SIZE 64
# define SPRITE_NBR 59

# define PI 3.14159265359

# define BALL_SPEED 9
# define PL_SPEED 3
# define ROTATION_SPEED 200
# define MAX_COINS 4

typedef enum	e_state
{
	DIED_STATE,
	WIN_STATE,
	GAME_STATE
}	t_state;

typedef enum	e_type
{
	FLOOR,
	DOOR,
	DOOR_OPEN,
	ENEMY,
	SPRITE,
	BALL,
	COLLECT,
	WALL
}	t_type;

typedef struct s_objs
{
	struct timespec last_time;
	double 			elapsed_time;
	int				spr_index;
	t_type			type;
	t_v2D			pos;
	int				state;
	int				hp;
}	t_objs;

typedef struct s_player
{
	t_v2D	pos;
	t_v2D	direction;
	t_v2D	plane;
	t_v2D	movement;
	t_list	*ball_node;
	int		hp;
	int		coins;
	double	angle;
	double	pitch;
	bool	mouse;
	bool	shoot;
	bool	anim;
}	t_player;

typedef struct s_map
{
	int		x;
	int		y;
	int		width;
	int		height;
	char	**game_map;
	char	*config_map[7];
}	t_map;

typedef struct s_image
{
	void	*img_ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_image;

typedef struct s_sprite
{
	t_image	img;
	int		height;
	int		width;
	int		color;
}	t_sprite;

typedef struct s_ray
{
	t_v2D	dir;
	t_v2D	delta;
	t_v2D	side_d;
	t_v2D	step;
}	t_ray;

typedef struct	s_draw
{
	int			tex_x;
	double		line_height;
	double		scale;
	double		tex_pos;
	int			start;
	int			end;
}	t_draw;

typedef struct s_cell
{
    int x;
    int y;
}              t_cell;

typedef struct s_mlx
{
	void			*lib;
	void			*window;
	t_sprite		sprite[SPRITE_NBR];
	t_player		player;
	t_map			map;
	t_image			img;
	t_ray			ray;
	t_draw			draw;
	t_list			*objs_lst;
	t_cell 			*marked_cells;
	t_state			game_state;
	int				side;
	double			dist_buffer[WIDTH];
    int 			num_marked_cells;
	int				spr_index;
	int				spr_hp_index;
	int				spr_character_index;
	int				spr_coins_index;
	struct timespec door_time;
	struct timespec last_time;
	struct timespec current_time;
	struct timespec prev_time;
	double elapsed_time;
	double elapsed_door;
	double	delta;
}	t_mlx;


t_player	init_player(double x, double y, char tile);
void		init_sprite(t_mlx *mlx, char **conf_map, t_sprite *sprite);
t_objs		*init_obj(t_v2D pos, int spr_index, int hp, t_type type);
t_list		*init_ball(t_list **head, t_player *player);
//Raycast
void		ft_grua(t_mlx *mlx);
t_draw		calculus(t_ray *ray, t_player *player, double *buffer , int side);
int			select_sprite(t_ray *ray, int side);
void		draw_line(t_mlx *mlx, int x);
void		door_hit(t_mlx *mlx, t_map *map);
void		sprite_loop(t_mlx *mlx);

//Enemy Raycast
void		enemy_ray(t_mlx *mlx, t_list *objs_lst);

// Update
void		update_player(t_mlx *mlx, t_player *player, t_map *map);
void		update_ball(t_mlx *mlx, t_player *player, char **game_map);
void		update_sprites(t_mlx *mlx, t_player *player, t_list *objs_lst);
void		update_animations(t_mlx *mlx);
void		update_state(t_mlx *mlx);
void		end_game(t_mlx *mlx);

// Game Loop
int			game_loop(t_mlx *mlx);

// Map
void		prepare_map(t_mlx *mlx);
t_map		init_map(char *map_name);


// Parser (MAP)
int			check_element(char *line);
int			check_path(char *line);
int			check_rgb(int **c, char *line);
int			check_conf(t_mlx *mlx, char **conf_map, t_sprite *sprite);
int			color(int nbr);
int			shift_color(int *rgb);
int			advance_space(char *line);

void		print_map(char **map);
int			map_parser(char *file_name, t_mlx *mlx);
int			create_config_map(t_map *map, char **full_map);
int			create_content_map(t_map *map, char **full_map, int after, int len);

// Image
void		pixel_put(t_image *img, int pixelX, int pixelY, int color);
int			pixel_get(t_image *img, int pixel_x, int pixel_y);
t_sprite	xpm_to_image(t_mlx *mlx, char *texture);
void		shoot_ball(t_mlx *mlx);
t_image		image_buffer(t_mlx *mlx);

// Events
int			handle_keyPress(int keycode, t_mlx *mlx);
int			handle_keyRelease(int keycode, t_player *player);
int			handle_mouse(int x, int y, t_mlx *mlx);
int			handle_mouse_press(int button, int x, int y, t_mlx *mlx);
t_v2D		rotate(t_v2D vector, double degree);

// Interactions
t_type		get_next_tile(char **game_map, t_player *player);
void		interact_door(char **game_map, t_player *player);
bool		check_objs_collision(t_mlx *mlx, t_list *objs_lst, t_v2D check);

// Draw Hud
void	draw_hud(t_mlx *mlx, int spr_index, t_v2D sprite_pos);
void	draw_char(t_mlx *mlx);
void	draw_coins(t_mlx *mlx);
void	draw_hearts(t_mlx *mlx);
int		calc_char_anim(t_mlx *mlx);
void	draw_end_game(t_mlx *mlx, int sprite);
void	draw_minimap(t_mlx *mlx, t_list *objs_lst);

// Sort Sprite
t_list	*sort_sprites(t_player *player, t_list *objs_lst);

// Time

void	update_time(struct timespec *time);
double	time_passed(struct timespec *last, struct timespec *current);

// Free Mem
void	free_list(t_list *lst);
void	print_list(t_list *lst);
void	elim_obj(t_list **head, t_list *elim_obj);
void	print_error(char *str, int statusm, t_mlx *mlx);
void	close_game(t_mlx *mlx, int status);

void	end_game_screen(t_mlx *mlx);
void	win_game_screen(t_mlx *mlx);

#endif