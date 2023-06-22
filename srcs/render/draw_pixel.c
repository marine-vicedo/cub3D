/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parida <parida@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:27:44 by pmaimait          #+#    #+#             */
/*   Updated: 2023/06/22 23:48:07 by parida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	 square(int num) {
    return num * num;
}

int	get_pixel(t_data *data)
{
	int	color;
	
	// double	ratio_y = TILE_SIZE / data->ray.wallStripHeight;
	// double 	ratio_x = square(TILE_SIZE) * SCWIDTH / data->ray.wallStripHeight / SCHEIGHT;
	int		tex_start;
	
	if (data->ray.side == 2 || data->ray.side == 3)
		tex_start = (int)round(data->ray.ray_x) % TILE_SIZE;
	else
		tex_start = (int)round(data->ray.ray_y) % TILE_SIZE;
	color = data->texture[data->ray.side].addr[tex_start * TILE_SIZE + tex_start];
	return (color);
}

void	render3DProjectWall(t_data *data)
{
	data->ray.correctionWallDistance = data->ray.ray_distance * cos(data->ray.ray_angle - data->player.rotationAngle);
    data->ray.distanceProjectionPlane = (SCWIDTH / 2) / tan(FOV_ANGLE / 2);
    data->ray.wallStripHeight  = (TILE_SIZE / data->ray.correctionWallDistance) * data->ray.distanceProjectionPlane;
	data->ray.draw_start_y = (SCHEIGHT / 2) - (data->ray.wallStripHeight / 2);
	if (data->ray.draw_start_y < 0)
		data->ray.draw_start_y = 0;
	while (data->ray.draw_start_y <= data->ray.wallStripHeight && data->ray.draw_start_y != SCHEIGHT)
	{
		data->ray.draw_start_x = data->ray.ray_id * Wall_STRIP_WIDTH;
		while (data->ray.draw_start_x <= (data->ray.ray_id * Wall_STRIP_WIDTH + Wall_STRIP_WIDTH))
		{
			// ft_my_mlx_pixel_put(&data->img, (int)data->ray.draw_start_y, (int)data->ray.draw_start_x, MMAP_COLOR_WALL);
			ft_my_mlx_pixel_put(&data->img, (int)data->ray.draw_start_y, (int)data->ray.draw_start_x, get_pixel(data));
			data->ray.draw_start_x++;
		}
		data->ray.draw_start_y++;
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
	data->ray.ray_distance = sqrt(square(fabs(x - data->player.pos_x)) + square(fabs(y - data->player.pos_y)));
	data->ray.ray_x = x;
	data->ray.ray_y = y;
	wall_side(data, x, y);
}
void	draw_ray(t_data *data)
{
	data->ray.ray_id = 0;
	
	data->ray.ray_angle = (data->player.rotationAngle - FOV_ANGLE / 2);
	while (data->ray.ray_angle <= (data->player.rotationAngle + FOV_ANGLE / 2))
	{
		data->ray.ray_x = data->player.pos_x;
		data->ray.ray_y = data->player.pos_y;
		draw_line(data, data->ray.ray_angle, data->ray.ray_x, data->ray.ray_y);
		render3DProjectWall(data);
		data->ray.ray_angle += 0.1 * (PI / 180);
		data->ray.ray_id++;
	}
}
