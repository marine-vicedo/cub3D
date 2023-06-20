/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaimait <pmaimait@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 11:59:34 by pmaimait          #+#    #+#             */
/*   Updated: 2023/06/19 11:58:30 by pmaimait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub3D.h"

void    start_game(t_data *data)
{
    data->mlx = mlx_init();
    if (!data->mlx)
        exit(1);
    data->win = mlx_new_window(data->mlx, SCWIDTH, SCHEIGHT, "cub3D");
	data->win_mini = mlx_new_window(data->mlx, (data->map.width * TILE_SIZE), (data->map.height * TILE_SIZE), "mini_map");
    if (!data->win || !data->win_mini)
        exit(1);
    init_img(data);
    //image_load(data);
    init_player(data);
	draw_minimap(data);
	updata(data);   
}