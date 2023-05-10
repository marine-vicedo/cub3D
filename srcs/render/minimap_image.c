/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_image.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaimait <pmaimait@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:28:30 by pmaimait          #+#    #+#             */
/*   Updated: 2023/05/10 15:19:21 by pmaimait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub3D.h"

void    draw_minimap(t_data *data)
{
    t_minimap   *minimap;
    int wid;
    int hei;
    int bits_per_pixel = 4;
    int endian = 1;
    int size_line = data->img.img_width * 50;
    
	minimap = &data->minimap;
	data->img.img = mlx_xpm_file_to_image(data->mlx, "./image/test1.xpm", &wid, &hei);
    char *img_data = mlx_get_data_addr(data->img.img, &bits_per_pixel, &size_line, &endian);
	int x = 100;
    int y = 100;
    int color = 0xFF0000; // Red color in hexadecimal format
    int pixel_index = (y * size_line) + (x * (bits_per_pixel / 8));
    *(int *)(img_data + pixel_index) = color;

    mlx_put_image_to_window(data->mlx, data->win, data->img.img, 100, 150);
    
}

