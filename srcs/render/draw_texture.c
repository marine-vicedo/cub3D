/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaimait <pmaimait@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:27:44 by pmaimait          #+#    #+#             */
/*   Updated: 2023/07/10 10:34:09 by pmaimait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

unsigned int	get_texture(t_data *data)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	int				tex_i;
	t_img			tex;

	tex = data->texture[data->ray.side];
	tex_i = (int)data->ray.offset_y * tex.line_size
		+ (int)data->ray.offset_x * tex.bits_per_pixel / 8;
	r = (unsigned char)(data->texture[data->ray.side].addr)[tex_i + 2];
	g = (unsigned char)(data->texture[data->ray.side].addr)[tex_i + 1];
	b = (unsigned char)(data->texture[data->ray.side].addr)[tex_i];
	return (((int)r << 16) | ((int)g << 8) | (int)b);
}

static void	get_texture_pos(t_data *data, int y)
{
	t_img	*tex;

	tex = &data->texture[data->ray.side];
	data->ray.offset_y = (y * tex->img_height) / data->ray.wall_strip_h;
	if (data->ray.side == 2 || data->ray.side == 3)
	{
		data->ray.offset_x = fmod(data->ray.ray_x, TILE_SIZE);
		if (data->ray.side == 2)
			data->ray.offset_x = TILE_SIZE - data->ray.offset_x;
	}
	else if (data->ray.side == 1 || data->ray.side == 0)
	{
		data->ray.offset_x = fmod(data->ray.ray_y, TILE_SIZE);
		if (data->ray.side == 1)
			data->ray.offset_x = TILE_SIZE - data->ray.offset_x;
	}
	data->ray.offset_x = (data->ray.offset_x * tex->img_width) / TILE_SIZE;
}

unsigned int	choose_color(t_data *data, double y)
{
	unsigned int	color;

	get_texture_pos(data, y);
	color = get_texture(data);
	return (color);
}

void	draw_texture(t_data *data, double x, double top_pxl)
{
	int		next;
	double	y;
	double	tmp_top_pxl;

	y = 0;
	next = x + Wall_STRIP_WIDTH;
	tmp_top_pxl = top_pxl;
	while (x < next)
	{
		y = 0;
		while (top_pxl < 0)
			top_pxl = tmp_top_pxl + y++;
		while (top_pxl < SCHEIGHT && y <= data->ray.wall_strip_h)
		{
			my_mlx_pixel_put(&data->img, x, top_pxl, choose_color(data, y));
			y += 1;
			top_pxl = tmp_top_pxl + y;
		}
		x++;
	}
}
