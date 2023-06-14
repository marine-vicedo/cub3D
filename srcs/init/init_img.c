/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaimait <pmaimait@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:25:51 by pmaimait          #+#    #+#             */
/*   Updated: 2023/06/13 14:44:45 by pmaimait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub3D.h"

void	init_img_clean(t_img *img)
{
	img->img = NULL;
	img->addr = NULL;
	img->bits_per_pixel = 0;
	img->line_length = 0;
	img->endian = 0;
}

void    init_img(t_data *data)
{
    init_img_clean(&data->img);
	data->img.img = mlx_new_image(data->mlx, SCWIDTH, SCHEIGHT);
	if (data->img.img == NULL)
		clean_exit(data, 1);
	data->img.addr = (int *)mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel,
			&data->img.line_length, &data->img.endian);
	return ;
}

void    init_player(t_data *data)
{
    t_player    *player;

    player = &data->player;
    player->radius = 3;
    player->turnDirection = 0;  // -1 if left, +1 if right
    player->walkDirection = 0;  // -1 if back, +1 if front
    player->rotationAngle = PI / 2;
    player->moveSpeed = 5;
    player->rotationSpeed = 1 * (PI / 180);
}

void    init_newPosition(t_data *data)
{
    t_player    *player;

    player = &data->player;
    player->turnDirection = 0;  // -1 if left, +1 if right
    player->walkDirection = 0;  // -1 if back, +1 if front
}