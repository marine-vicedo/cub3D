/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parida <parida@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:25:51 by pmaimait          #+#    #+#             */
/*   Updated: 2023/06/29 20:57:58 by parida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub3D.h"

void	init_img_clean(t_img *img)
{
	img->img = NULL;
	img->addr = NULL;
	img->bits_per_pixel = 0;
	img->line_size = 0;
	img->endian = 0;
}

void	init_img_clean_data(t_data *data)
{
	// data->img = NULL;
	data->img.img = NULL;
	data->img.addr = NULL;
	data->img.bits_per_pixel = 0;
	data->img.line_size = 0;
	data->img.endian = 0;
}

void	init_texture(t_data *data)
{
	/* east = 0, west = 1, south = 2, north = 3 */
	char	*path;
	int		i;

	i = 0;
	   while (i < 4)
	{	
		if (i == 0)
			path = data->file.east;
		else if (i == 1)
			path = data->file.west;
		else if (i == 2)
			path = data->file.south;
		else
			path = data->file.north;
		data->texture[i].img = \
			mlx_xpm_file_to_image(data->mlx, path, &data->texture[i].img_width, &data->texture[i].img_height);
		if (data->texture[i].img_width != TILE_SIZE || data->texture[i].img_height != TILE_SIZE
			|| data->texture[i].img == NULL)
				exit_game(data);
		data->texture[i].addr = mlx_get_data_addr(data->texture[i].img, \
					&data->texture[i].bits_per_pixel, &data->texture[i].line_size, &data->texture[i].endian);
		if (!data->texture[i].addr)
			exit_game(data);
		i++;
	}
}

void     init_img(t_data *data)
{
    init_img_clean_data(data);
	data->img.img = mlx_new_image(data->mlx, SCWIDTH, SCHEIGHT);
	if (data->img.img == NULL)
		exit_game(data);
	data->img.addr = mlx_get_data_addr(data->img.img, \
					&data->img.bits_per_pixel, &data->img.line_size, &data->img.endian);
	if (data->img.addr == NULL)
		exit_game(data);
	data->img.ratio = 1;
	return ;
}

void	init_textures(t_data *data)
{
	data->texture = (t_img *)malloc(sizeof(t_img) * 4);
	if (!data->texture)
		exit(1);
	init_texture(data);
}

void    init_player(t_data *data)
{
    t_player    *player;

    player = &data->player;
    player->turnDirection = 0;  // -1 if left, +1 if right
    player->walkDirection = 0;  // -1 if back, +1 if front
}

void    init_newPosition(t_data *data)
{
    t_player    *player;

    player = &data->player;
    player->turnDirection = 0;  // -1 if left, +1 if right
    player->walkDirection = 0;  // -1 if back, +1 if front
}

t_pixel	init_pixel(int x, int y, int color)
{
	t_pixel	p;

	p.x = x;
	p.y = y;
	p.color = color;
	return (p);
}