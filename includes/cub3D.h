/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parida <parida@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 13:30:58 by pmaimait          #+#    #+#             */
/*   Updated: 2023/07/01 22:54:22 by parida           ###   ########.fr       */
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
# include <limits.h>
# include <unistd.h>
# include <string.h>

# ifndef BONUS
#  define BONUS 1
# endif

# define SCHEIGHT 600
# define SCWIDTH 960
# define FOV_ANGLE  1.047197551

# define K_A 97
# define K_D 100
# define K_S 115
# define K_W 119
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

# define K_ESC 65307

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
# define TILE_SIZE 64
# define Wall_STRIP_WIDTH 1
# define NUM_RAY 960
# define moveSpeed 5
# define rotationSpeed 5 * (PI / 180)
# define WINDOW 1
# define MINI_MAP 2

# define ERR_FILE_NOT_CUB "Extension file is not .cub"
# define ERR_FILE_NOT_XPM "Extension file is not .xpm"
# define ERR_FILE_TOO_BIG "File is too big"
# define ERR_FILE_TOO_SMALL "Not enough informations to start"
# define ERR_MAP_WALLS "Map is not surrounded by walls"

# define FREE 1

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}				t_rgb;

typedef struct s_pixel
{
	int				x;
	int				y;
	unsigned int	color;
}			t_pixel;

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_size;
	int			endian;
	int			img_width;
	int			img_height;
	double		ratio;
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

typedef struct s_file
{
	int			line_count;
	char		**content;
	int			height;
	int			width;
	char		*north;
	char		*south;
	char		*west;
	char		*east;
	int			floor;
	int			ceiling;
	int			flag;
}				t_file;

typedef struct s_map
{
	char	**map;
	int		size;
	int		x;
	int		y;
	int		width;
	int		height;
}				t_map;

typedef struct s_player
{
	int			status;
	double		pos_x;
	double		pos_y;
	int			radius;
	int			turnDirection;
	int			walkDirection;
	double		rotationAngle;
}				t_player;

typedef struct s_ray
{
	double			offset_y;
	double			offset_x;
	double			wallStripHeight;
	double			correctionWallDistance;
	double			distanceProjectionPlane;
	int				side;
	int				ray_id;
	double			draw_start_x;
	double			draw_start_y;
	int			ray_x;
	int			ray_y;
	double			ray_angle;
	double			ray_distance;
	
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
	t_img	m_map;
}	t_minimap;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	void		*win_mini;
	t_file		file;
	t_map		map;
	t_rgb		rgb;
	t_img		img;
	t_img		*texture;
	t_player	player;
	t_ray		ray;
	t_move		move;
	t_minimap	minimap;
}				t_data;

//move/
//keypress
int				handle_keypress(int keysym, t_data *data);
int				handle_keyrelease(int keysym, t_data *data);
void			updata(t_data *data);
int				hasWallAt(t_data *data, double x, double y);


//init/
//init_img
void			init_img_clean(t_img *img);
void			init_img(t_data *data);
void			init_player(t_data *data);
void			init_newPosition(t_data *data);
void			init_textures(t_data *data);
void			init_texture(t_data *data);
t_pixel			init_pixel(int x, int y, int color);
//start_game
void    		start_game(t_data *data);


//render/
//minimap_image;
void			draw_window(t_data *data);
//draw_pixel
void			draw_line(t_data *data, double angle, double x, double y);
void			draw_ray(t_data *data);
void			render3DProjectWall(t_data *data);
void			draw_wall(t_data *data, int x, int y, int color);
void			wall_side(t_data *data, double x, double y);
unsigned int	get_color(t_data *data, double x, double y);


//painting
void			paint_floor(t_data *data);
void			paint_img(t_data *data);


//utils/
//position
void			get_position_player(t_data *data);
void			set_image_pixel(t_img *image, int x, int y, int color);
void			ft_my_mlx_pixel_put(t_img *data, int i, int j, int color);
void    		my_mlx_pixel_put(t_img *data, int x, int y, int color);
unsigned int    get_texture(t_data *data);
//exit
void			clean_exit(t_data *data, int code);
int				quit_cub3d(t_data *data);
int				exit_game(t_data *data);
void			clean_texture(t_data *data);

//main

int			main_loop(t_data *data);


//parsing/
//parsing_file
int				ft_parsing_map(char *av, t_data *data);
int				ft_file_content(t_data *data, t_file *file);
void			ft_copy_fileinfo(char *av, t_data *data);
int				ft_count_lines(t_data *data, char *file);
//textures_colors_check
int				ft_check_fileinfo(t_data *data, t_file *file, char *str);
int				ft_direction_check(t_file *file, char *str);
int				ft_color_check(t_file *file, char *str, char c);
//textures_colors_utils
char			*ft_direction_path(char *str);
int				set_rgb(char **line);
int				check_format_numbers(char *str);
int				ft_is_xpm_file(char *path);
//parsing_map
int				ft_check_mapfile(t_data *data,
					t_file *file, char *str, int space);
int				ft_is_valid_minimap(t_data *data, t_player *p, char *line);
//get_map
int				ft_fill_map(t_map *map, char **map_file, int index);
void			ft_free_map(char **tab);
int				get_map(t_data *data, t_file *file);
//walls_check
int				ft_check_walls(t_map *map, char **map_m);
int				ft_check_empty_space(t_map *map, char **map_m);
int				ft_check_space_around(char **map_m, int i, int j);
int				check_player_pos(int c);
//parsing_utils
char			*ft_strdup_no_nl(const char *s);
int				ft_isspace(char c);
int				ft_strlen_m(const char *s);
//exit_error
void			ft_free_data(t_data *data);
void			ft_free_map(char **tab);
void			err_msg(char *msg);
int 			exit_clean(t_data *data, char *msg, int code);

//libft
// char	*get_next_line(int fd);
// char	*ft_strdup(const char *s);
// int		ft_strncmp(const char *s1, const char *s2, size_t n);
int 	ft_isdigit(int c);
// int		ft_atoi(const char *str);
// size_t	ft_strlen(const char *s);
void	ft_print_map(char **tab);
// void	ft_putstr_fd(char *s, int fd);

#endif