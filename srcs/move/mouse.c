/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicedo <mvicedo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 11:23:51 by mvicedo           #+#    #+#             */
/*   Updated: 2023/07/07 16:30:29 by mvicedo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	mouse_button_handler(int button, int x, int y, t_data *data)
{
	static int	old_x = SCWIDTH / 2;

	(void)y;
	if (button == 1)
	{
		if (x == old_x)
		return (0);
		else if (x < old_x)
			data->player.turn_dir = -1;
		else if (x > old_x)
			data->player.turn_dir = +1;
		update(data);
		draw_window(data);
	}
	return (0);
}


