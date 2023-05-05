/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaimait <pmaimait@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:29:30 by pmaimait          #+#    #+#             */
/*   Updated: 2023/05/05 11:29:49 by pmaimait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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