/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_image.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parida <parida@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:28:30 by pmaimait          #+#    #+#             */
/*   Updated: 2023/07/04 21:49:35 by parida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub3D.h"

void	put_img(t_data *data, int x, int y)
{
	if (data->map.map[y][x] == '1')
		mlx_put_image_to_window(data->mlx, data->win_mini, data->minimap.wall,
			x * TILE_SIZE, y * TILE_SIZE);
}

void	setting_img(t_data *data)
{
	int	x;
	int	y;

	data->minimap.wall = mlx_xpm_file_to_image(data->mlx,
			"./image/color_stone.xpm", &x, &y);
	y = 0;
	while (y < data->map.height)
	{
		x = 0;
		while (x < data->map.width)
		{
			put_img(data, x, y);
			x++;
		}
		y++;
	}
}

/* void	setting_img(t_data *data)
{
	int	x;
	int	y;

	//data->minimap.wall = mlx_xpm_file_to_image(data->mlx, "./image/color_stone.xpm", &x, &y);
	y = 0;
	while (y < data->map.height * data->m_map.ratio)
	{
		x = 0;
		while (x < data->map.width * data->m_map.ratio)
		{
			if (hasWallAt(data, x / data->m_map.ratio, y / data->m_map.ratio))
				my_mlx_pixel_put(&data->m_map, x, y, MMAP_COLOR_WALL);
			x++;
		}
		y++;
	}
} */

void	draw_window(t_data *data)
{
	mlx_clear_window(data->mlx, data->win_mini);
	mlx_destroy_image(data->mlx, data->img.img);
	//mlx_destroy_image(data->mlx, data->m_map.img);
	data->img.img = mlx_new_image(data->mlx, SCWIDTH, SCHEIGHT);
	if (data->img.img == NULL)
		clean_exit(data, 1);
	setting_img(data);
	paint_floor(data);
	draw_ray(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	//mlx_put_image_to_window(data->mlx, data->win, data->m_map.img, 10, 10);
	init_new_position(data);
}
