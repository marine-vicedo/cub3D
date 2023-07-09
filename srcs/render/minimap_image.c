/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_image.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parida <parida@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:28:30 by pmaimait          #+#    #+#             */
/*   Updated: 2023/07/09 10:48:15 by parida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub3D.h"

void	put_img(t_data *data, int x, int y)
{
	if (data->map.map[y][x] == '1')
		my_mlx_pixel_put(&data->m_map, (x / TILE_SIZE * data->m_map.ratio),
			(y / TILE_SIZE * data->m_map.ratio), MMAP_COLOR_WALL);
}

void	setting_img(t_data *data)
{
	int		x;
	int		y;
	double	ratio;

	ratio = data->m_map.ratio;
	y = 0;
	while (y < data->map.height * ratio)
	{
		x = 0;
		while (data->map.map[(int)(y / ratio)][(int)(x / ratio)]
				&& x < data->map.width * ratio)
		{
			my_mlx_pixel_put(&data->m_map, x, y, MMAP_COLOR_FLOOR);
			if (data->map.map[(int)(y / ratio)][(int)(x / ratio)] == '1')
				my_mlx_pixel_put(&data->m_map, x, y, MMAP_COLOR_WALL);
			x++;
		}
		y++;
	}
}

void	draw_window(t_data *data)
{
	if (BONUS)
	{
		mlx_destroy_image(data->mlx, data->m_map.img);
		data->m_map.img = mlx_new_image(data->mlx,
				(data->map.width * data->m_map.ratio),
				(data->map.height * data->m_map.ratio));
		if (data->m_map.img == NULL)
			exit_game(data);
		setting_img(data);
	}
	mlx_destroy_image(data->mlx, data->img.img);
	data->img.img = mlx_new_image(data->mlx, SCWIDTH, SCHEIGHT);
	if (data->img.img == NULL)
		clean_exit(data, 1);
	paint_floor(data);
	draw_ray(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	if (BONUS)
		mlx_put_image_to_window(data->mlx, data->win, data->m_map.img, 10, 10);
	init_new_position(data);
}
