/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaimait <pmaimait@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:25:51 by pmaimait          #+#    #+#             */
/*   Updated: 2023/06/22 15:40:51 by pmaimait         ###   ########.fr       */
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
    img->arr_img = NULL;
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
		if (data->texture[i].img_width != TEX_SIZE || data->texture[i].img_height != TEX_SIZE
			|| data->texture[i].img == NULL)
			{
				printf("there is no image in textue");
				exit_game(data);
			}
		data->texture[i].addr = mlx_get_data_addr(data->texture[i].img, \
					&data->texture[i].bits_per_pixel, &data->texture[i].line_size, &data->texture[i].endian);
		if (!data->texture[i].addr)
			exit_game(data);
		i++;
	}
}

void     init_img(t_data *data)
{
    init_img_clean(&data->img);
	data->img.img = mlx_new_image(data->mlx, SCWIDTH, SCHEIGHT);
	if (data->img.img == NULL)
		exit_game(data);
	data->img.addr = mlx_get_data_addr(data->img.img, \
					&data->img.bits_per_pixel, &data->img.line_size, &data->img.endian);
	if (data->img.addr == NULL)
		exit_game(data);
	init_textures(data);
	return ;
}

void	init_textures(t_data *data)
{
	data->texture = (t_img *)malloc(sizeof(t_img) * 4);
	if (!data->texture)
		exit(1);
	init_texture(data);
}
/* void	image_load(t_data *data)
{
	char	*path;
	int		i;

	i = 1;
	   while (i < 5)
	{	
		if (i == 1)
			path = data->file.east;
		else if (i == 2)
			path = data->file.west;
		else if (i == 3)
			path = data->file.south;
		else
			path = data->file.north;
		data->img.img = \
			mlx_xpm_file_to_image(data->mlx, path, &data->img.img_width, &data->img.img_height);
		if (data->img.img_width != TEX_SIZE || data->img.img_height != TEX_SIZE
			|| data->img.img == NULL)
			exit(1);
		data->img.addr = mlx_get_data_addr(data->img.img, \
					&data->img.bits_per_pixel, &data->img.line_size, &data->img.endian);
		fill_arr_img(data, i);
		mlx_destroy_image(data->mlx, data->img.img);
		i++;
	}
} */


void    init_player(t_data *data)
{
    t_player    *player;

    player = &data->player;
    player->radius = 3;
    player->turnDirection = 0;  // -1 if left, +1 if right
    player->walkDirection = 0;  // -1 if back, +1 if front
    player->moveSpeed = 5;
    player->rotationSpeed = 5 * (PI / 180);
}

void    init_newPosition(t_data *data)
{
    t_player    *player;

    player = &data->player;
    player->turnDirection = 0;  // -1 if left, +1 if right
    player->walkDirection = 0;  // -1 if back, +1 if front
}