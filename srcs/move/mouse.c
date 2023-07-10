/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaimait <pmaimait@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 11:23:51 by mvicedo           #+#    #+#             */
/*   Updated: 2023/07/10 10:54:22 by pmaimait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

long long	get_current_time_ms(void)
{
	struct timespec	now;

	clock_gettime(CLOCK_MONOTONIC, &now);
	return (now.tv_sec * 1000LL + now.tv_nsec / 1000000LL);
}

int	mouse_button_handler(int button, int x, int y, t_data *data)
{
	static long long int	last_click_time = 0;
	long long int			current_time;

	(void)y;
	if (button == 1)
	{
		current_time = get_current_time_ms();
		if ((current_time
				- last_click_time) <= (long long int)DOUBLE_CLICK_DELAY)
		{
			if ((x >= ((SCWIDTH / 2) - 100) && x <= (SCWIDTH / 2 + 100)))
				data->player.walk_dir = -1;
		}
		else
		{
			if (x < (SCWIDTH / 2 - 30))
				data->player.turn_dir = -1;
			else if (x > (SCWIDTH / 2 + 30))
				data->player.turn_dir = +1;
		}
		last_click_time = current_time;
		update(data);
		draw_window(data);
	}
	return (0);
}
