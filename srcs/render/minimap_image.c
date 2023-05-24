/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_image.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaimait <pmaimait@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:28:30 by pmaimait          #+#    #+#             */
/*   Updated: 2023/05/24 14:31:03 by pmaimait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub3D.h"
void	put_img(t_data *data, int x, int y)
{
	if (data->minimap.map[y][x] == 'P')
		 draw_circle(data, (x * 50) + 25, (y * 50) + 25, 10, 0xFF0000); // Red color;
	else if (data->minimap.map[y][x] == '1' || data->minimap.map[y][x] == '2' || data->minimap.map[y][x] == '3'|| data->minimap.map[y][x] == '4')
		mlx_put_image_to_window(data->mlx, data->win, data->minimap.wall, x * 50, y * 50);
}

void	setting_img(t_data *data)
{
	int	x;
	int	y;

	data->minimap.wall = mlx_xpm_file_to_image(data->mlx, "./image/test1.xpm", &x, &y);
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


void    draw_minimap(t_data *data)
{
    setting_img(data);
	init_player(data);
}

