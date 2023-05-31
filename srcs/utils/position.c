/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position->mapc                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicedo <mvicedo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:07:48 by pmaimait          #+#    #+#             */
/*   Updated: 2023/05/31 14:33:03 by mvicedo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub3D.h"

void    get_position_player(t_data *data)
{
    t_player    *player;
    t_map       *map;
    int     i;
    int     j; 

    j = 0;
    player = &data->player;
	map = &data->map;
    while (j < map->height )
    {
        i = 0;
        while (i < map->width)
        {
			//printf("%c", minimap->map[j][i]);
            if (map->map[j][i] == 'N' || map->map[j][i] == 'S' || map->map[j][i] == 'E' || map->map[j][i] == 'W')
            {
                player->pos_x = (i * TILE_SIZE) + TILE_SIZE / 2;
                player->pos_y = (j * TILE_SIZE) + TILE_SIZE / 2;
            }
            i++;
        }
		//printf("\n");
        j++;
    }
}
