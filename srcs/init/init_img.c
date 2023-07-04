/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parida <parida@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:25:51 by pmaimait          #+#    #+#             */
/*   Updated: 2023/07/04 21:43:13 by parida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_img_clean(t_img *img)
{
	img->img = NULL;
	img->addr = NULL;
	img->bits_per_pixel = 0;
	img->line_size = 0;
	img->endian = 0;
}

void	init_img(t_data *data)
{
	init_img_clean(&data->img);
	data->img.img = mlx_new_image(data->mlx, SCWIDTH, SCHEIGHT);
	if (data->img.img == NULL)
		exit_game(data);
	data->img.addr = mlx_get_data_addr(data->img.img, \
			&data->img.bits_per_pixel, &data->img.line_size,
			&data->img.endian);
	if (data->img.addr == NULL)
		exit_game(data);
	data->img.ratio = 1;
	return ;
}

// t_pixel	init_pixel(int x, int y, int color)
// {
// 	t_pixel	p;

// 	p.x = x;
// 	p.y = y;
// 	p.color = color;
// 	return (p);
// }

double	get_minimap_ratio(t_data *data)
{
	double	ratio;

	if (data->map.width > data->map.height)
		ratio = (SCWIDTH * 30) / data->map.width;
	else
		ratio = (SCHEIGHT * 30) / data->map.height;
	return (ratio / 100);
}

void     init_img_mini(t_data *data)
{
	data->m_map.ratio = get_minimap_ratio(data);
	data->m_map.img = NULL;
    init_img_clean(&data->m_map);
	data->m_map.img = mlx_new_image(data->mlx, (data->map.width  * data->m_map.ratio), (data->map.height * data->m_map.ratio));
	if (data->m_map.img == NULL)
		exit_game(data);
	data->m_map.addr = mlx_get_data_addr(&data->m_map, \
					&data->m_map.bits_per_pixel, &data->m_map.line_size, &data->m_map.endian);
	if (data->m_map.addr == NULL)
		exit_game(data);
	return ;
}