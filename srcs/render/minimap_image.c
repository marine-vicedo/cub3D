/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_image.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicedo <mvicedo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:28:30 by pmaimait          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/06/14 11:55:13 by pmaimait         ###   ########.fr       */
=======
/*   Updated: 2023/05/31 15:04:00 by mvicedo          ###   ########.fr       */
>>>>>>> Marine
/*                                                                            */
/* ************************************************************************** */

#include"cub3D.h"
void	put_img(t_data *data, int x, int y)
{
	if (data->map.map[y][x] == '1')
<<<<<<< HEAD
		mlx_put_image_to_window(data->mlx, data->win_mini, data->minimap.wall, x * TILE_SIZE, y * TILE_SIZE);
=======
		mlx_put_image_to_window(data->mlx, data->win_mini, data->minimap.wall, x * 50, y * 50);
>>>>>>> Marine
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
	mlx_clear_window(data->mlx, data->win_mini);
	mlx_clear_window(data->mlx, data->win);
    setting_img(data);
	//draw_circle(data); // Red color;
	//draw_line(data, data->player.rotationAngle, data->player.pos_x, data->player.pos_y);
	draw_ray(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	mlx_destroy_image(data->mlx, data->img.img);
	init_newPosition(data);
}

