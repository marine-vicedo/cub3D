/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parida <parida@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:25:51 by pmaimait          #+#    #+#             */
/*   Updated: 2023/06/09 14:20:54 by parida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub3D.h"

/* void    init_img(t_data *data)
{
    t_img   *img;

    img = &data->img;
    // img->img_width = 24;
    // img->img_height = 24;
} */

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