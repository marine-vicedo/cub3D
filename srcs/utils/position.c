/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parida <parida@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 15:41:40 by mvicedo           #+#    #+#             */
/*   Updated: 2023/07/09 23:07:50 by parida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub3D.h"

static void	player_direction(t_data *data, char c)
{
	if (c == 'N')
		data->player.rotate_angle = PI / 2;
	if (c == 'E')
		data->player.rotate_angle = PI;
	if (c == 'S')
		data->player.rotate_angle = PI * 3 / 2;
	if (c == 'W')
		data->player.rotate_angle = 0;
}

void	get_position_player(t_data *data)
{
	t_player	*player;
	t_map		*map;
	int			i;
	int			j;

	j = 0;
	player = &data->player;
	map = &data->map;
	while (j < map->height)
	{
		i = 0;
		while (map->map[j][i] && i < map->width)
		{
			if (map->map[j][i] == 'N' || map->map[j][i] == 'S'
				|| map->map[j][i] == 'E' || map->map[j][i] == 'W')
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

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + y * img->line_size + x * img->bits_per_pixel / 8;
	*(unsigned int *)dst = color;
}
