/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_image.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parida <parida@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:28:30 by pmaimait          #+#    #+#             */
/*   Updated: 2023/05/13 00:08:19 by parida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub3D.h"
void	put_img(t_data *data, int x, int y)
{
	if (data->minimap.map[y][x] == 'P')
		 mlx_put_image_to_window(data->mlx, data->win, data->minimap.player, x * 50, y * 50);
	else if (data->minimap.map[y][x] == '1' || data->minimap.map[y][x] == '2' || data->minimap.map[y][x] == '3'|| data->minimap.map[y][x] == '4')
		mlx_put_image_to_window(data->mlx, data->win, data->minimap.wall, x * 50, y * 50);
}

void	setting_img(t_data *data)
{
	int	x;
	int	y;

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
    t_minimap   *minimap;
    int wid;
    int hei;
    int bits_per_pixel = 4;
    int endian = 1;
    int size_line = data->img.img_width * 50;
    
	minimap = &data->minimap;
	minimap->wall = mlx_xpm_file_to_image(data->mlx, "./image/test1.xpm", &wid, &hei);
    minimap->player = mlx_xpm_file_to_image(data->mlx, "./image/P.xpm", &wid, &hei);
    char *img_data = mlx_get_data_addr(minimap->wall, &bits_per_pixel, &size_line, &endian);
	int x = 100;
    int y = 100;
    int color = 0xFF0000; // Red color in hexadecimal format
    int pixel_index = (y * size_line) + (x * (bits_per_pixel / 8));
    *(int *)(img_data + pixel_index) = color;
    setting_img(data);
}

