/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parida <parida@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 15:30:43 by mvicedo           #+#    #+#             */
/*   Updated: 2023/07/04 21:48:43 by parida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	render_3d_wall(t_data *data)
{
	data->ray.draw_start_x = data->ray.ray_id * Wall_STRIP_WIDTH;
	data->ray.corr_wall_distance = data->ray.ray_distance
		* cos(data->ray.ray_angle - data->player.rotate_angle);
	data->ray.projection_plane = (SCWIDTH / 2) / tan(FOV_ANGLE / 2);
	data->ray.wall_strip_h = (TILE_SIZE / data->ray.corr_wall_distance)
		* data->ray.projection_plane ;
	data->ray.draw_start_y = (SCHEIGHT / 2) - (data->ray.wall_strip_h / 2);
	draw_texture(data, data->ray.draw_start_x, data->ray.draw_start_y);
}

void	wall_side(t_data *data, double x, double y)
{
	int	n;
	int	e;
	int	w;
	int	s;

	n = 1;
	e = 1;
	w = 1;
	s = 1;
	if (has_wall_at(data, (x + 1), y))
		w = 0;
	if (has_wall_at(data, (x - 1), y))
		e = 0;
	if (has_wall_at(data, x, (y + 1)))
		n = 0;
	if (has_wall_at(data, x, (y - 1)))
		s = 0;
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
	angle = angle - PI;
	while (!has_wall_at(data, x, y))
	{
		mlx_pixel_put(data->mlx, data->win_mini, x, y, MMAP_COLOR_PLAYER);
		//my_mlx_pixel_put(&data->m_map, (x * data->m_map.ratio), (y * data->m_map.ratio), MMAP_COLOR_PLAYER);
		x += cos(angle);
		y += sin(angle);
	}
	data->ray.ray_distance = sqrt(pow(x - data->player.pos_x, 2)
			+ pow(y - data->player.pos_y, 2));
	data->ray.ray_x = x;
	data->ray.ray_y = y;
	wall_side(data, x, y);
}

void	draw_ray(t_data *data)
{
	data->ray.ray_id = 0;
	data->ray.ray_angle = (data->player.rotate_angle - FOV_ANGLE / 2);
	while (data->ray.ray_id < NUM_RAY)
	{
		data->ray.ray_x = data->player.pos_x;
		data->ray.ray_y = data->player.pos_y;
		draw_line(data, data->ray.ray_angle, data->ray.ray_x, data->ray.ray_y);
		render_3d_wall(data);
		data->ray.ray_angle += FOV_ANGLE / NUM_RAY;
		data->ray.ray_id++;
	}
}
