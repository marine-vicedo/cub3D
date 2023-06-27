/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaimait <pmaimait@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:27:44 by pmaimait          #+#    #+#             */
/*   Updated: 2023/06/27 15:37:26 by pmaimait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	 square(int num) {
    return num * num;
}

void	draw_pixel(t_data *data, t_pixel p, int option)
{
	int		size;
	int		window_width;
	int		window_height;
	t_img	*img;

	if (option == WINDOW)
	{
		window_width = SCWIDTH;
		window_height = SCHEIGHT;
		img = data->img.img;
	}
	else
	{
		window_width = (data->map.width * TILE_SIZE);
		window_height = (data->map.height * TILE_SIZE);
		img = data->minimap.m_map.img;
	}
	size = window_width * img->ratio;
	if ((p.x >= 0 && p.x < window_width * img->ratio) && \
			(p.y >= 0 && p.y < window_height * img->ratio))
		img->addr[p.x + size * p.y] = p.color;
}

int	get_color(t_data *data, int x, double y)
{
	unsigned int	color_index;
	unsigned int	color;
	double	ratio = data->texture[data->ray.side].img_height / data->ray.wallStripHeight;
	unsigned int		tex_start;
	(void)x;
	if (data->ray.side == 2 || data->ray.side == 3)
		tex_start = (int)round(data->ray.ray_x) % TILE_SIZE;
	else
		tex_start = (int)round(data->ray.ray_y) % TILE_SIZE;
	if (tex_start < (unsigned int)data->texture[data->ray.side].img_width && (y * ratio) < (unsigned int)data->texture[data->ray.side].img_height)
		color_index = (tex_start * data->texture[data->ray.side].line_size) +  (y * ratio) * (data->texture[data->ray.side].bits_per_pixel / 8);
	else
		color_index= (tex_start - 1) * data->texture[data->ray.side].line_size +  y * ratio * (data->texture[data->ray.side].bits_per_pixel / 8);
	color = get_texture(data, color_index);
	return (color);
}

void	render3DProjectWall(t_data *data)
{
	int	color;
	double	y;
	
	data->ray.correctionWallDistance = data->ray.ray_distance * cos(data->ray.ray_angle - data->player.rotationAngle);
    data->ray.distanceProjectionPlane = (SCWIDTH / 2) / tan(FOV_ANGLE / 2);
    data->ray.wallStripHeight  = (TILE_SIZE / data->ray.correctionWallDistance) * data->ray.distanceProjectionPlane;
	data->ray.draw_start_y = (SCHEIGHT / 2) - (data->ray.wallStripHeight / 2);
	
	data->ray.draw_start_x = data->ray.ray_id * Wall_STRIP_WIDTH;
	while (data->ray.draw_start_x <= (data->ray.ray_id * Wall_STRIP_WIDTH + Wall_STRIP_WIDTH))
	{
		y = 0;
		data->ray.draw_start_y = (SCHEIGHT / 2) - (data->ray.wallStripHeight / 2) + y;
		while (data->ray.draw_start_y < 0)
			data->ray.draw_start_y = SCHEIGHT / 2 - (data->ray.wallStripHeight / 2) + y++;
		while (data->ray.draw_start_y < SCHEIGHT)
		{
			// draw_pixel(data, init_pixel(data->ray.draw_start_x, data->ray.draw_start_y, get_color(data, data->ray.draw_start_x, data->ray.draw_start_y)), WINDOW);
			color = get_color(data, (int)data->ray.draw_start_x, y);
			ft_my_mlx_pixel_put(&data->img, (int)data->ray.draw_start_y, (int)data->ray.draw_start_x, color);
			y += 1;
			data->ray.draw_start_y = (SCHEIGHT / 2) - (data->ray.wallStripHeight / 2) + y;
			if (y >= data->ray.wallStripHeight)
				break ;
		}
		data->ray.draw_start_x++;
	}
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
