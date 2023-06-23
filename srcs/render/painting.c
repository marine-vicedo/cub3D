/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaimait <pmaimait@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 14:37:58 by pmaimait          #+#    #+#             */
/*   Updated: 2023/06/23 15:43:21 by pmaimait         ###   ########.fr       */
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
	while (i < SCHEIGHT)
	{
		j = 0;
		while (j < SCWIDTH)
		{
			if (i <= SCHEIGHT / 2)
				ft_my_mlx_pixel_put(&data->img, i, j, celling);
			else
				ft_my_mlx_pixel_put(&data->img, i, j, floor);
			j++;
		}
		i++;
	}	
}
