/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parida <parida@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 14:37:58 by pmaimait          #+#    #+#             */
/*   Updated: 2023/07/03 20:20:58 by parida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	paint_floor(t_data *data)
{
	int	x;
	int	y;
	int	celling;
	int	floor;

	y = 0;
	celling = data->file.ceiling;
	floor = data->file.floor;
	while (y < SCHEIGHT)
	{
		x = 0;
		while (x < SCWIDTH)
		{
			if (y <= SCHEIGHT / 2)
				my_mlx_pixel_put(&data->img, x, y, celling);
			else
				my_mlx_pixel_put(&data->img, x, y, floor);
			x++;
		}
		y++;
	}	
}
