/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaimait <pmaimait@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 15:29:33 by pmaimait          #+#    #+#             */
/*   Updated: 2023/07/11 10:13:36 by pmaimait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_cub(t_data *data)
{
	init_img(data);
	if (BONUS)
		init_img_mini(data);
	init_textures(data);
	init_player(data);
	get_position_player(data);
}

void	start_cub(t_data *data)
{
	data->win = mlx_new_window(data->mlx, SCWIDTH, SCHEIGHT, "cub3D");
	if (data->win == NULL)
	{
		free(data->win);
		free(data);
		exit_game(data);
	}
	draw_window(data);
	update(data);
	mlx_hook(data->win, 2, 1L << 0, handle_keypress, data);
	if (BONUS)
		mlx_hook(data->win, BUTTONPRESS, (1L << 2), mouse_button_handler,
			data);
	mlx_hook(data->win, 17, 1L << 0, exit_game, data);
	mlx_loop(data->mlx);
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (ac != 2)
		return (free(data),
			printf("Error\nCub3D need one argument (ex : map.cub)\n"),
			1);
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
