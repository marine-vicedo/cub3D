/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaimait <pmaimait@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 15:29:33 by pmaimait          #+#    #+#             */
/*   Updated: 2023/05/30 15:41:18 by pmaimait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub3D.h"


int	render(t_data *data)
{
	draw_minimap(data);
	return (0);
}

int main(int ac, char **av)
{
	t_data	data;

	data.mlx= mlx_init();
	if (data.mlx== NULL || ac != 2)
		return (1);
	init_img(&data);
	get_position_player(&data, av[1]);
	
    data.win = mlx_new_window(data.mlx, 960, 600, "cub3D");
	data.win_mini = mlx_new_window(data.mlx, (data.map.width * TILE_SIZE), (data.map.height * TILE_SIZE), "mini_map");
	if (data.win_mini == NULL || data.win == NULL)
	{
		free(data.win_mini);
		free(data.win);
		return (1);
	}
	init_player(&data);
	draw_minimap(&data);
	updata(&data);

	
	
	/* Setup hooks */ 
	//mlx_loop_hook(data.mlx, &render, &data);
	mlx_hook(data.win_mini, 2, 1L << 0, &handle_keypress, &data);
	//mlx_hook(data.win_mini, 3, 1L << 0, &handle_keyrelease, &data);
	mlx_hook(data.win_mini, 17, 1L << 0, &exit_game, &data);
	mlx_loop(data.mlx);

	/* we will exit the loop if there's no window left, and execute this code */
	mlx_destroy_display(data.mlx);
	free(data.mlx);
	return (0);
}

