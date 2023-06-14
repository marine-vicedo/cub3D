/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaimait <pmaimait@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 13:30:58 by pmaimait          #+#    #+#             */
/*   Updated: 2023/06/14 11:54:51 by pmaimait         ###   ########.fr       */
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
# define TILE_SIZE 50

#define ERR_FILE_NOT_CUB "Extension file is not .cub"
#define ERR_FILE_TOO_BIG "File is too big"
#define ERR_FILE_TOO_SMALL "Not enough informations to start"
#define ERR_MAP_WALLS "Map is not surrounded by walls"

#define FREE 1

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}				t_rgb;

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	/* int			img_width;
	int			img_height;
	int			buffer[SCHEIGHT][SCWIDTH];
	int			**arr_img; */
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
	//int			mcount;
	//int			start;
	int			flag;
}				t_file;

typedef struct s_map
{
	char	**map;
	int		size;
	int		x;
	int		y;
	int		width;
	int 	height;
}				t_map;

typedef struct s_player
{
	int			status;
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
	int			radius;
	int			turnDirection;
	int			walkDirection;
	double		rotationAngle;
	int			moveSpeed;
	double		rotationSpeed;
}				t_player;

typedef struct s_ray
{
	// double		camera_x;
	// double		dir_x;
	// double		dir_y;
	// int			map_x;
	// int			map_y;
	// int			step_x;
	// int			step_y;
	// double		sidedist_x;
	// double		sidedist_y;
	// double		deltadist_x;
	// double		deltadist_y;
	// double		wall_dist;
	// double		wall_x;
	// int			side;
	// int			line_height;
	// int			draw_start;
	// int			draw_end;
	double			ray_x;
	double			ray_y;
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
void    		init_player(t_data *data);
void    		init_newPosition(t_data *data);

//render/
//minimap_image;
void    		draw_minimap(t_data *data);

//utils/
//position
void    		get_position_player(t_data *data);
//draw_pixel
void			draw_line(t_data *data, double angle, double x, double y, int ray_id);
void			draw_ray(t_data *data);
void			render3DProjectWall(t_data *data, int ray_id);
void			draw_wall(t_data *data, double x, double y, int color);
//exit
void			clean_exit(t_data *data, int code);
int				quit_cub3d(t_data *data);
int				exit_game(t_data *data);


//parsing/
int	ft_parsing_map(char *av, t_data *data);
void	ft_copy_fileinfo(char *av, t_file *file);
int	ft_file_content(t_data *data, t_file *file);
int	ft_count_lines(char *file);
int	ft_check_fileinfo(t_data *data, t_file *file, char *str);
int	get_map(t_data *data, t_file *file);
void	ft_fd_error(void);
void	ft_str_error(void);
int	ft_color_check(t_file *file, char *str, char c);
int set_rgb(char **line);
int	check_format_numbers(char *str);
size_t ft_strcspn(const char *s, const char *reject);
char	*ft_strdup_no_nl(const char *s);
int	ft_check_mapfile(t_data *data, t_file *file, char *str);
int	ft_is_valid_minimap(t_data *data, t_player *p, char *line);
int	ft_fill_map(t_map *map, char **map_file, int index);
void	ft_free_data(t_data *data);
void	ft_free_map(char **tab);
int ft_check_walls(t_map *map, char **map_m);
int	ft_check_empty_space(t_map *map, char **map_m);
void	err_msg(char *msg);
int exit_clean(t_data *data, char *msg, int code);

//libft
// char	*get_next_line(int fd);
// char	*ft_strdup(const char *s);
// int		ft_strncmp(const char *s1, const char *s2, size_t n);
int 	ft_isspace(char c);
int 	ft_isdigit(int c);
// int		ft_atoi(const char *str);
// size_t	ft_strlen(const char *s);
void	ft_print_map(char **tab);
// void	ft_putstr_fd(char *s, int fd);

#endif