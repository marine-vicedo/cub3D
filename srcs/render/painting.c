/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaimait <pmaimait@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 14:37:58 by pmaimait          #+#    #+#             */
/*   Updated: 2023/06/20 15:39:37 by pmaimait         ###   ########.fr       */
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
			ft_my_mlx_pixel_put(&data->img, i, j, celling);
			ft_my_mlx_pixel_put(&data->img, (SCHEIGHT - i - 1), j, floor);
			j++;
		}
		i++;
	}	
}
