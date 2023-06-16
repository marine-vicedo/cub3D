/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaimait <pmaimait@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:25:51 by pmaimait          #+#    #+#             */
/*   Updated: 2023/06/16 15:26:02 by pmaimait         ###   ########.fr       */
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

void	fill_arr_img(t_data *data, int i)
{
	int	y;
	int	x;

	y = 0;
	while (y < data->img.img_height)
	{
		x = 0;
		while (x < data->img.img_width)
		{
			data->img.arr_img[i][data->img.img_width * y + x] = \
				data->img.addr[data->img.img_height * y + x];
			x++;
		}
		y++;
	}
}

void    init_img(t_data *data)
{
    int i;
    int	j;
	
    init_img_clean(&data->img);
	data->img.img = mlx_new_image(data->mlx, SCWIDTH, SCHEIGHT);
	if (data->img.img == NULL)
		clean_exit(data, 1);
	i = 0;
	while (i < SCHEIGHT)
	{
		j = 0;
		while (j < SCWIDTH)
			data->img.buffer[i][j++] = 0;
		i++;
	}
	data->img.arr_img = (int **)malloc(5 * sizeof(int *));
	if (!data->img.arr_img)
		exit(1);
	i = 0;
	while (i < 5)
	{
		data->img.arr_img[i] = (int *)malloc(sizeof(int) * TEX_SIZE * TEX_SIZE);
		if (!data->img.arr_img[i])
			exit(1);
		ft_memset(data->img.arr_img[i], 0, (sizeof(int) * TEX_SIZE * TEX_SIZE));
		i++;
	}
	
 
	return ;
}
void	image_load(t_data *data)
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