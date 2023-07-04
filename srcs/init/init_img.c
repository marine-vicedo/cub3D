/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicedo <mvicedo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:25:51 by pmaimait          #+#    #+#             */
/*   Updated: 2023/07/04 14:44:48 by mvicedo          ###   ########.fr       */
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