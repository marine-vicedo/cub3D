/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaimait <pmaimait@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 13:30:58 by pmaimait          #+#    #+#             */
/*   Updated: 2023/05/24 15:02:05 by pmaimait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx.h"
# include "../libft/includes/get_next_line.h"
# include "../libft/includes/libft.h"
# include <fcntl.h>  /*for open */
# include <errno.h>  /*for perror strerror */
# include <math.h>   /*for sin, cos, aqrt, etc...*/
# include <stdio.h>  /* for printf , open, read, write */
# include <stdlib.h> /*for malloc, free, exit */

# define SCHEIGHT 720
# define SCWIDTH 960

# define K_A 97
# define K_B 98
# define K_C 99
# define K_D 100
# define K_E 101
# define K_F 102
# define K_G 103
# define K_H 104
# define K_I 105
# define K_J 106
# define K_K 107
# define K_L 108
# define K_M 109
# define K_N 110
# define K_O 111
# define K_P 112
# define K_Q 113
# define K_R 114
# define K_S 115
# define K_T 116
# define K_U 117
# define K_V 118
# define K_W 119
# define K_X 120
# define K_Y 121
# define K_Z 124

/*
** Keyboard ARROWS
*/

# define K_AR_L 65361
# define K_AR_R 65363
# define K_AR_U 65362
# define K_AR_D 65364
/*
**Keyboard MISC
*/

# define K_SP 32
# define K_ESC 65307
# define K_TAB 65289

/*
** Mouse
*/

# define M_CLK_L 1
# define M_CLK_R 3
# define M_CLK_M 2
# define M_SCR_U 4
# define M_SCR_D 5

/* MINIMAP MACROS */
# define MMAP_PIXEL_SIZE 128
# define MMAP_VIEW_DIST 4
# define MMAP_COLOR_PLAYER 0x00FF00
# define MMAP_COLOR_WALL 0x808080
# define MMAP_COLOR_FLOOR 0xE6E6E6
# define MMAP_COLOR_SPACE 0x404040


# define PI 3.14159
# define TILE_SIZE 50


	typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			img_width;
	int			img_height;
	int			buffer[SCHEIGHT][SCWIDTH];
	int			**arr_img;
}				t_img;

typedef struct s_move
{
	int			key_w;
	int			key_s;
	int			key_a;
	int			key_d;
	int			arr_l;
	int			arr_r;
}				t_move;

typedef struct s_map
{
	int			line_count;
	char		**file;
	int			height;
	int			width;
	char		*north;
	char		*south;
	char		*west;
	char		*east;
	int			floor;
	int			celling;
	int			mcount;
	int			start;
	int			ret;
}				t_map;

typedef struct s_player
{
	//char		dir;
	double		pos_x;
	double		pos_y;
	//double		dir_x;
	//double		dir_y;
	//double		plane_x;
	//double		plane_y;
	//int			has_moved;
	//int			move_x;
	//int			move_y;
	//int			rotation;
	double		newPlayerX;
	double		newplayerY;
	int			radius;
	int			turnDirection;
	int			walkDirection;
	int			rotationAngle;
	int			moveSpeed;
	int			rotationSpeed;
}				t_player;

typedef struct s_ray
{
	double		camera_x;
	double		dir_x;
	double		dir_y;
	int			map_x;
	int			map_y;
	int			step_x;
	int			step_y;
	double		sidedist_x;
	double		sidedist_y;
	double		deltadist_x;
	double		deltadist_y;
	double		wall_dist;
	double		wall_x;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
}				t_ray;

typedef struct s_minimap
{
	char	**map;
	int		size;
	int		offset_x;
	int		offset_y;
	int		view_dist;
	int		tile_size;
	void	*wall;
	void	*player;
}	t_minimap;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_map		map;
	t_img		img;
	t_player	player;
	t_ray		ray;
	t_move		move;
	t_minimap	minimap;
}				t_data;

//move/
//keypress
int				handle_keypress(int keysym, t_data *data);
int				handle_keyrelease(int keysym, t_data *data);
int				exit_game(t_data *data);
void			updata(t_data *data);
int				hasWallAt(t_data *data, double x, double y);


//init/
//init_img
void			init_img(t_data *data);
void    		init_player(t_data *data);

//render/
//minimap_image;
void    		draw_minimap(t_data *data);

//utils/
//position
void    		get_position_player(t_data *data, char *map);
//draw_pixel
void			draw_circle(t_data *tata, int center_x, int center_y, int diameter, int color);
#endif