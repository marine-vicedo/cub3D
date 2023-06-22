/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parida <parida@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 14:36:14 by pmaimait          #+#    #+#             */
/*   Updated: 2023/06/22 20:17:22 by parida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	clean_texture(t_data *data)
{
	if (data->texture[0].img)
		mlx_destroy_image(data->mlx, data->texture[0].img);
	if (data->texture[1].img)
		mlx_destroy_image(data->mlx, data->texture[1].img);
	if (data->texture[2].img)
		mlx_destroy_image(data->mlx, data->texture[2].img);
	if (data->texture[3].img)
		mlx_destroy_image(data->mlx, data->texture[3].img);
	free(data->texture);
}

void	clean_exit(t_data *data, int code)
{
	if (!data)
		exit(code);
	if (data->win && data->mlx)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		mlx_loop_end(data->mlx);
		free(data->mlx);
	}
	free(data);
	exit(code);
}

int	quit_cub3d(t_data *data)
{
	clean_exit(data, 0);
	return (0);
}

int	exit_game(t_data *data)
{
	mlx_destroy_image(data->mlx, data->minimap.wall);
	mlx_destroy_image(data->mlx, data->img.img);
	clean_texture(data);
	ft_free_data(data);
	if (data->win && data->mlx && data->win_mini)
	{
		mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_window(data->mlx, data->win_mini);
	}
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		mlx_loop_end(data->mlx);
		free(data->mlx);
	}
	free(data);
	exit (0);
	return (0);
}