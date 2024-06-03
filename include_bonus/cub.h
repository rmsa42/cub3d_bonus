/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/06/03 16:31:40 by rumachad         ###   ########.fr       */
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

# define ESC 65307
# define W 119
# define A 97
# define S 115
# define D 100
# define E 101
# define LARROW 65361
# define RARROW 65363

# define HEIGHT 600
# define WIDTH 800
# define FOV 90
# define SPRITE_SIZE 64
# define MAX_OBJS 100

# define PI 3.14159265359
# define GREEN 	0x0000FF00

# define SPEED 0.02
# define ROTATION_SPEED 3

# define CEILING_S 4
# define FLOOR_S 5

#define NO 0
#define SO 1
#define EA 2
#define WE 3
#define F 4
#define C 5

typedef enum	s_type
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
	CEILING,
	FLOOR,
	DOOR,
	DOOR_OPEN,
	ENEMIE,
	WALL
}	t_type;

typedef struct s_player
{
	t_v2D	pos;
	t_v2D	direction;
	t_v2D	plane;
	t_v2D	movement;
	double	angle;
	double	fov;
	double	pitch;
	bool	key;
}	t_player;

typedef struct s_map
{
	int		x;
	int		y;
	int		total_lines;
	int		lines_to_map;
	char	**game_map;
	char	**anim_map;
	char	*config_map[6];
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

typedef struct	s_tile
{
	t_type	type;
	t_v2D	pos;
}	t_tile;

typedef struct s_objs
{
	t_type	type;
	t_v2D	pos;
	int		state;
}	t_objs;

typedef struct s_mlx
{
	char		*file;
	void		*lib;
	void		*window;
	t_sprite	sprite[14];
	t_player	player;
	t_map		map;
	t_image		img;
	t_ray		ray;
	t_draw		draw;
	char		**event_map;
	int			spr_index;
	double		camera;
	int			side;
	double		dist_buffer[WIDTH];
	t_objs		objs[MAX_OBJS];
	int			map_width;
	int			map_height;
	char **map2;
}	t_mlx;


t_player	init_player(double x, double y, char tile);
//Raycast
void		ft_grua(t_mlx *mlx);
t_draw		calculus(t_ray *ray, t_player *player, double *buffer , int side);
int			select_sprite(t_ray *ray, int side);
void		draw_line(t_mlx *mlx, int x);
void		door_hit(t_mlx *mlx, t_map *map);
void		sprite_loop(t_mlx *mlx);

// Update
void		update(t_mlx *mlx);
void		update_sprites(t_mlx *mlx);

//Render
int			render(t_mlx *mlx);

// Map
void		map_draw(t_mlx *mlx);
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
int			color(int nbr);
int			advance_space(char *line);

void		print_map(char **map);
int			ft_check_filename(t_mlx *mlx);
void    	ft_read_file_and_copy_map(char *file, t_mlx *mlx);

// Image
void		pixel_put(t_image *img, int pixelX, int pixelY, int color);
int			pixel_get(t_image *img, int pixel_x, int pixel_y);
t_sprite	xpm_to_image(t_mlx *mlx, char *texture);
void		image_to_window(t_mlx *mlx, void *img_ptr, int x, int y);

// Events
int			handle_keyPress(int keycode, t_mlx *mlx);
int			handle_keyRelease(int keycode, t_player *player);

t_tile	get_next_tile(char **game_map, t_player *player);
void	interact_door(t_tile *tile, char **game_map, t_player *player);

void		close_game(t_mlx *mlx);
void			ft_perror(char *msg, t_mlx *mlx);

#endif