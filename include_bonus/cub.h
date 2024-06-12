/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/06/12 11:37:33 by cacarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include "vector2D.h"
# include <assert.h>
# include <stdbool.h>
#include <time.h>

# define ESC 65307
# define W 119
# define A 97
# define S 115
# define D 100
# define E 101
# define Q 113
# define LARROW 65361
# define RARROW 65363

# define HEIGHT 600
# define WIDTH 800
# define FOV 90
# define SPRITE_SIZE 64
# define SPRITE_NBR 52

# define PI 3.14159265359

# define SPEED 0.02
# define ROTATION_SPEED 3

# define NO 0
# define SO 1
# define EA 2
# define WE 3
# define F 4
# define C 5

typedef enum	s_type
{
	FLOOR,
	DOOR,
	DOOR_OPEN,
	ENEMY,
	SPRITE,
	WALL
}	t_type;

typedef struct s_player
{
	t_v2D	pos;
	t_v2D	direction;
	t_v2D	plane;
	t_v2D	movement;
	int		hp;
	double	angle;
	double	fov;
	double	pitch;
	bool	key;
	bool	mouse;
	bool	shoot;
	bool	anim;
}	t_player;

typedef struct s_map
{
	int		x;
	int		y;
	int		total_lines;
	int		lines_to_map;
	char	**game_map;
	char	*config_map[7];
	char	**map_copy;
	char	**flood_map;
	bool	NO_flag;
	bool	SO_flag;
	bool	EA_flag;
	bool	WE_flag;
	bool	F_flag;
	bool	C_flag;
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

typedef struct s_objs
{
	struct timespec last_time;
	double elapsed_time;
	int		spr_index;
	t_type	type;
	t_v2D	pos;
	int		state;
	int		hp;
}	t_objs;

typedef struct s_cell
{
    int x;
    int y;
}              t_cell;

typedef struct s_mlx
{
	char		*file;
	void		*lib;
	void		*window;
	t_sprite	sprite[SPRITE_NBR];
	t_player	player;
	t_map		map;
	t_image		img;
	t_ray		ray;
	t_draw		draw;
	int			spr_index;
	int			side;
	double		dist_buffer[WIDTH];
	t_list		*objs_lst;
	int			map_width;
	int			map_height;
	t_cell 		*marked_cells;
    int 		num_marked_cells;
	t_v2D		ball_pos;
	int			test;
	struct timespec door_time;
	struct timespec last_time;
	struct timespec current_time;
	double elapsed_time;
	double elapsed_door;
}	t_mlx;


t_player	init_player(double x, double y, char tile);
void		init_sprite(void *lib, char **conf_map, t_sprite *sprite);
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
void		update_sprites(t_mlx *mlx, t_player *player, t_list *objs_lst);

//Render
int			render(t_mlx *mlx);

// Map
void		prepare_map(t_mlx *mlx);
t_map		init_map(char *map_name);
void 		ft_check_b4_init(int ac, char **av, t_mlx *mlx);
void    	ft_check_game_map(t_mlx *mlx);
void		ft_copy_config_map(t_mlx *mlx);
void 		ft_copy_game_map(t_mlx *mlx);
int			ft_check_all_config_flags(t_mlx *mlx);
void		ft_count_map_lines(t_mlx *mlx);

// Parser (MAP)
int			check_element(char *line);
int			check_path(char *line);
int			check_rgb(int **cc, char *line);
int			check_conf(void *lib, char **conf_map, t_sprite *sprite);
int			color(int nbr);
int			shift_color(int *rgb);
int			advance_space(char *line);

void		print_map(char **map);
int			ft_check_filename(t_mlx *mlx);
void    	ft_read_file_and_copy_map(char *file, t_mlx *mlx);

// Image
void		pixel_put(t_image *img, int pixelX, int pixelY, int color);
int			pixel_get(t_image *img, int pixel_x, int pixel_y);
t_sprite	xpm_to_image(void *lib, char *texture);
void		shoot_ball(t_mlx *mlx);

// Events
int			handle_keyPress(int keycode, t_mlx *mlx);
int			handle_keyRelease(int keycode, t_player *player);
int			handle_mouse(int x, int y, t_mlx *mlx);
t_v2D		rotate(t_v2D vector, int degree);

// Interactions
t_type		get_next_tile(char **game_map, t_player *player);
void		interact_door(char **game_map, t_player *player);

void		close_game(t_mlx *mlx);
void		ft_perror(char *msg, t_mlx *mlx);

// Draw Hud
void	draw_hp(t_mlx *mlx);
void	draw_char(t_mlx *mlx, int char_anim, t_v2D sprite_pos);
int		calc_char_anim(t_mlx *mlx);
void draw_end_game(t_mlx *mlx);

// Time

void	update_time(struct timespec *time);
double	time_passed(struct timespec *last, struct timespec *current);

#endif