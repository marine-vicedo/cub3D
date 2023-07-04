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

static void player_direction(t_data *data, char c)
{
    if (c == 'N')
        data->player.rotationAngle = PI / 2;
    if (c == 'E')
        data->player.rotationAngle = PI;
    if (c == 'S')
        data->player.rotationAngle = PI * 3 / 2;
    if (c == 'W')
        data->player.rotationAngle = 0;
}

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
            if (map->map[j][i] == 'N' || map->map[j][i] == 'S' || map->map[j][i] == 'E' || map->map[j][i] == 'W')
            {
                player->pos_x = (i * TILE_SIZE) + TILE_SIZE / 2;
                player->pos_y = (j * TILE_SIZE) + TILE_SIZE / 2;
                player_direction(data, map->map[j][i]);
            }
            i++;
        }
        j++;
    }
}

void	set_image_pixel(t_img *image, int x, int y, int color)
{
	int	pixel;

	pixel = x + y * SCWIDTH;
	image->addr[pixel] = color;
}

void    my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
    char    *dst;

    dst = img->addr + y * img->line_size + x * img->bits_per_pixel / 8;
    *(unsigned int *)dst = color;
}
