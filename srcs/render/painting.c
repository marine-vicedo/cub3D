/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaimait <pmaimait@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 14:37:58 by pmaimait          #+#    #+#             */
/*   Updated: 2023/06/16 14:42:10 by pmaimait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	paint_floor(t_data *data)
{
	int	i;
	int	j;
	int	celling;
	int	floor;

	i = 0;
	celling = data->file.ceiling;
	floor = data->file.floor;
	while (i < SCHEIGHT / 2)
	{
		j = 0;
		while (j < SCWIDTH)
		{
			data->img.buffer[i][j] = celling;
			data->img.buffer[SCHEIGHT - i - 1][j] = floor;
			j++;
		}
		i++;
	}	
}

void	paint_img(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < SCHEIGHT)
	{
		x = 0;
		while (x < SCWIDTH)
		{
			data->img.addr[y * SCWIDTH + x] = data->img.buffer[y][x];
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
}