/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parida <parida@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:27:44 by pmaimait          #+#    #+#             */
/*   Updated: 2023/06/22 20:59:57 by parida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	render3DProjectWall(t_data *data, int ray_id)
{
	double correctionWallDistance;
	double distanceProjectionPlane;
	double	wallStripHeight;
	double	Wall_STRIP_WIDTH;
	double	i;
	double	j;
	
	correctionWallDistance = data->ray.ray_distance * cos(data->ray.ray_angle - data->player.rotationAngle);
    distanceProjectionPlane = (SCWIDTH / 2) / tan(FOV_ANGLE / 2);
    wallStripHeight  = (TILE_SIZE / correctionWallDistance) * distanceProjectionPlane;
	j = (SCHEIGHT / 2) - (wallStripHeight / 2);
	Wall_STRIP_WIDTH = 1.6;
	if (j < 0)
		j = 0;
	while (j <= wallStripHeight && j != SCHEIGHT)
	{
		i = ray_id * Wall_STRIP_WIDTH;
		while (i <= (ray_id * Wall_STRIP_WIDTH + Wall_STRIP_WIDTH))
		{
			ft_my_mlx_pixel_put(&data->img, (int)j, (int)i, MMAP_COLOR_WALL);
			i++;
		}
		j++;
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
static int	 square(int num) {
    return num * num;
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
	int	ray_id = 0;
	
	data->ray.ray_angle = (data->player.rotationAngle - FOV_ANGLE / 2);
	while (data->ray.ray_angle <= (data->player.rotationAngle + FOV_ANGLE / 2))
	{
		data->ray.ray_x = data->player.pos_x;
		data->ray.ray_y = data->player.pos_y;
		draw_line(data, data->ray.ray_angle, data->ray.ray_x, data->ray.ray_y);
		render3DProjectWall(data, ray_id);
		data->ray.ray_angle += 0.1 * (PI / 180);
		ray_id++;
	}
}
