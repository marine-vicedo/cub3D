/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parida <parida@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:27:44 by pmaimait          #+#    #+#             */
/*   Updated: 2023/06/29 22:43:23 by parida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	 square(int num) {
    return num * num;
}

unsigned int    get_texture(t_data *data)
{
    int                res;
    int                tex_i;
    unsigned char    r;
    unsigned char    g;
    unsigned char    b;
	
    tex_i = data->ray.offset_y * data->texture[data->ray.side].line_size + data->ray.offset_x \
            * (data->texture[data->ray.side].bits_per_pixel / 8);
    r = (unsigned char)(data->texture[data->ray.side].addr)[tex_i + 2];
    g = (unsigned char)(data->texture[data->ray.side].addr)[tex_i + 1];
    b = (unsigned char)(data->texture[data->ray.side].addr)[tex_i];
    res = ((int)r << 16) + ((int)g << 8) + (int)b;
    return (res);
}


static void	get_texture_pos(t_data *data, int y)
{
	t_img    *tex;

    tex = &data->texture[data->ray.side];
    data->ray.offset_y = (y * tex->img_height) / floor(data->ray.wallStripHeight);
    if (data->ray.offset_y > tex->img_height)
        data->ray.offset_y = tex->img_height - 1;
    if (data->ray.side == 2 || data->ray.side == 3)
	{
		data->ray.offset_x = data->ray.ray_x / TILE_SIZE * TILE_SIZE;
		data->ray.offset_x = data->ray.ray_x  - data->ray.offset_x ;
		if (data->ray.side == 3)
			data->ray.offset_x = TILE_SIZE - data->ray.offset_x;
	}
	else if (data->ray.side == 1 || data->ray.side == 0)
	{
		data->ray.offset_x = data->ray.ray_y / TILE_SIZE * TILE_SIZE;
		data->ray.offset_x = data->ray.ray_y  - data->ray.offset_x ;
		if (data->ray.side == 0)
			data->ray.offset_x = TILE_SIZE - data->ray.offset_x;
	}
    data->ray.offset_x = (data->ray.offset_x * tex->img_width) / TILE_SIZE;
    if (data->ray.offset_x > tex->img_width)
        data->ray.offset_x = tex->img_width - 1;
}

unsigned int    choose_color(t_data *data, double y)
{
    unsigned int    color;
	
	get_texture_pos(data, y);
    color = get_texture(data);
    return (color);
}
static void	raycasting_draw_wall_texture(t_data *data, double x, double top_pxl)
{
	int		next;
	double	y;
	double	tmp_top_pxl;

	y = 0;
	next = x + Wall_STRIP_WIDTH;
	tmp_top_pxl = top_pxl;
	while (x < next)
	{
		y = 0;
		top_pxl = tmp_top_pxl + y;
		while (top_pxl < 0)
            top_pxl = tmp_top_pxl + y++;
		while (top_pxl < SCHEIGHT)
		{
			my_mlx_pixel_put(&data->img, x, top_pxl, \
						choose_color(data, y));
			y += 1;
			top_pxl = tmp_top_pxl + y;
			if (y > data->ray.wallStripHeight)
				break ;
		}
		x++;
	}
}

void	render3DProjectWall(t_data *data)
{
	data->ray.draw_start_x = data->ray.ray_id * Wall_STRIP_WIDTH;;
	data->ray.correctionWallDistance = data->ray.ray_distance * cos(data->ray.ray_angle - data->player.rotationAngle);
    data->ray.distanceProjectionPlane = (SCWIDTH / 2) / tan(FOV_ANGLE / 2);
    data->ray.wallStripHeight  = (TILE_SIZE / data->ray.correctionWallDistance) * data->ray.distanceProjectionPlane;
	data->ray.draw_start_y = (SCHEIGHT / 2) - (data->ray.wallStripHeight / 2);
	raycasting_draw_wall_texture(data, data->ray.draw_start_x , data->ray.draw_start_y);
}

void	wall_side(t_data *data, double x, double y)
{
	int	n;
	int e;
	int w;
	int s;
	/* east = 0, west = 1, south = 2, north = 3 */
	n = 1;
	e = 1;
	w = 1;
	s = 1;
	if(hasWallAt(data, (x + 1), y))
		e = 0;
	if(hasWallAt(data, (x - 1), y))
		w = 0;
	if(hasWallAt(data, x, (y + 1)))
		s = 0;
	if(hasWallAt(data, x, (y - 1)))
		n = 0;
	if (e == 1)
		data->ray.side = 0;
	if (w == 1)
		data->ray.side = 1;
	if (s == 1)
		data->ray.side = 2;
	if (n == 1)
		data->ray.side = 3;
}

void	draw_line(t_data *data, double angle, double x, double y)
{
	double i = 0;

	angle = angle - PI;
	
	while (i < INT_MAX)
	{
		mlx_pixel_put(data->mlx, data->win_mini, x, y, MMAP_COLOR_PLAYER);
		x = x + cos(angle);
		y = y + sin(angle);
		if (hasWallAt(data, x, y))
			break;
		i++;
	}
	data->ray.ray_distance = sqrt(square(x - data->player.pos_x) + square(y - data->player.pos_y));
	data->ray.ray_x = x;
	data->ray.ray_y = y;
	wall_side(data, x, y);
}
void	draw_ray(t_data *data)
{
	data->ray.ray_id = 0;
	data->ray.ray_angle = (data->player.rotationAngle - FOV_ANGLE / 2);
	while(data->ray.ray_id < NUM_RAY)
	{
		data->ray.ray_x = data->player.pos_x;
		data->ray.ray_y = data->player.pos_y;
		draw_line(data, data->ray.ray_angle, data->ray.ray_x, data->ray.ray_y);
		render3DProjectWall(data);
		data->ray.ray_angle += FOV_ANGLE / NUM_RAY;
		data->ray.ray_id++;
	}
}
