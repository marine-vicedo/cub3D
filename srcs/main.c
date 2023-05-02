/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaimait <pmaimait@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 15:29:33 by pmaimait          #+#    #+#             */
/*   Updated: 2023/05/02 15:02:26 by pmaimait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub3D.h"

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == K_ESC)
		mlx_destroy_window(data->mlx, data->win);

	printf("Keypress: %d\n", keysym);
	return (0);
}

int	handle_keyrelease(int keysym, void *data)
{
    (void)data;
	printf("Keyrelease: %d\n", keysym);
	return (0);
}

int	exit_game(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	exit (0);
	return (0);
}

int	main(void)
{
	t_data	data;

	data.mlx= mlx_init();
	if (data.mlx== NULL)
		return (1);
	data.win = mlx_new_window(data.mlx, SCWIDTH, SCHEIGHT, "My first window!");
	if (data.win == NULL)
	{
		free(data.win);
		return (1);
	}

	/* Setup hooks */ 
	//mlx_loop_hook(data.mlx, &handle_no_event, &data);
    mlx_hook(data.win, 17, 1L << 0, &exit_game, &data);
	mlx_hook(data.win, 2, 1L << 0, &handle_keypress, &data); 
	mlx_hook(data.win, 3, 1L << 0, &handle_keyrelease, &data);

	mlx_loop(data.mlx);

	/* we will exit the loop if there's no window left, and execute this code */
	mlx_destroy_display(data.mlx);
	free(data.mlx);
}