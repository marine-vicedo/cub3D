/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicedo <mvicedo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 15:29:33 by pmaimait          #+#    #+#             */
/*   Updated: 2023/07/04 15:43:36 by mvicedo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_cub(t_data *data)
{
	init_img(data);
	init_textures(data);
	init_player(data);
	get_position_player(data);
}

void	start_cub(t_data *data)
{
	data->win = mlx_new_window(data->mlx, SCWIDTH, SCHEIGHT, "cub3D");
	data->win_mini = mlx_new_window(data->mlx, (data->map.width * TILE_SIZE),
			(data->map.height * TILE_SIZE), "mini_map");
	if (data->win_mini == NULL || data->win == NULL)
	{
		free(data->win_mini);
		free(data->win);
		free(data);
		exit_game(data);
	}
	draw_window(data);
	update(data);
	mlx_hook(data->win_mini, 2, 1L << 0, handle_keypress, data);
	mlx_hook(data->win_mini, 17, 1L << 0, exit_game, data);
	mlx_hook(data->win, 17, 1L << 0, exit_game, data);
	mlx_loop(data->mlx);
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (ac != 2)
		return (free(data),
			printf("Error\nCub3D need one argument (ex : map.cub)\n"), 1);
	ft_parsing(data, av[1]);
	data->mlx = mlx_init();
	if (data->mlx == NULL || ac != 2)
		return (free(data), 1);
	init_cub(data);
	start_cub(data);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	free(data);
	return (0);
}
