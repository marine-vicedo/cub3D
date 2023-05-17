/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaimait <pmaimait@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 15:29:33 by pmaimait          #+#    #+#             */
/*   Updated: 2023/05/17 15:48:41 by pmaimait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub3D.h"


#define screenWidth 640
#define screenHeight 480


int main(int ac, char **av)
{
	t_data	data;

	data.mlx= mlx_init();
	if (data.mlx== NULL || ac != 2)
		return (1);
	init_img(&data);
	get_position_player(&data, av[1]);
	
   
	data.win = mlx_new_window(data.mlx, (data.map.width * 50), (data.map.height * 50), "My test window!");
	if (data.win == NULL)
	{
		free(data.win);
		return (1);
	}
	draw_minimap(&data);
	/* Setup hooks */ 
	//mlx_loop_hook(data.mlx, &handle_no_event, &data);
	mlx_hook(data.win, 17, 1L << 0, &exit_game, &data);
	mlx_hook(data.win, 2, 1L << 0, &handle_keypress, &data); 
	mlx_hook(data.win, 3, 1L << 0, &handle_keyrelease, &data);

	mlx_loop(data.mlx);

	/* we will exit the loop if there's no window left, and execute this code */
	mlx_destroy_display(data.mlx);
	free(data.mlx);
	return (0);
}