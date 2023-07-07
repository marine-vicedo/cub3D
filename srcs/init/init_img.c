/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicedo <mvicedo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:25:51 by pmaimait          #+#    #+#             */
/*   Updated: 2023/07/07 13:51:28 by mvicedo          ###   ########.fr       */
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
	img->img_width = 0;
	img->img_height = 0;
}

void	init_img(t_data *data)
{
	data->img.ratio = 1;
	init_img_clean(&data->img);
	data->img.img = mlx_new_image(data->mlx, SCWIDTH, SCHEIGHT);
	if (data->img.img == NULL)
		exit_game(data);
	data->img.addr = mlx_get_data_addr(data->img.img, \
			&data->img.bits_per_pixel, &data->img.line_size,
			&data->img.endian);
	if (data->img.addr == NULL)
		exit_game(data);
	return ;
}

double	get_minimap_ratio(t_data *data)
{
	double	ratio;

	if (data->map.width > data->map.height)
		ratio = (SCWIDTH * 30) / data->map.width;
	else
		ratio = (SCHEIGHT * 30) / data->map.height;
	return (ratio / 100);
}

void	init_img_mini(t_data *data)
{
	data->m_map.ratio = get_minimap_ratio(data);
	init_img_clean(&data->m_map);
	data->m_map.img = mlx_new_image(data->mlx,
			(data->map.width * data->m_map.ratio),
			(data->map.height * data->m_map.ratio));
	if (data->m_map.img == NULL)
		exit_game(data);
	data->m_map.addr = mlx_get_data_addr(data->m_map.img, \
			&data->m_map.bits_per_pixel,
			&data->m_map.line_size, &data->m_map.endian);
	if (data->m_map.addr == NULL)
		exit_game(data);
	return ;
}
