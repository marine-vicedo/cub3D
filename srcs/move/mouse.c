/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parida <parida@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 11:23:51 by mvicedo           #+#    #+#             */
/*   Updated: 2023/07/09 22:51:31 by parida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

long long get_current_time_ms()
{
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    return now.tv_sec * 1000LL + now.tv_nsec / 1000000LL;
}

int mouse_button_handler(int button, int x, int y, t_data *data)
{
    static int old_x = SCWIDTH / 2;
    static long long int last_click_time = 0;
    static int click_count = 0;
    long long int current_time = 0;

    (void)y;
    if (button == 1)
    {
        current_time = get_current_time_ms();

        if ((current_time - last_click_time) <= (long long int)DOUBLE_CLICK_DELAY)
        {
            click_count++;
            if (click_count == 1 && (x >= (old_x - 100) && x <= (old_x + 100)))
            {
                data->player.walk_dir = -1; // Execute double-click action
                click_count = 0; // Reset click count
            }
        }
        else
        {
            click_count = 0; // Reset click count for a new click
			if (x < (old_x - 30))
                data->player.turn_dir = -1;
            else if (x > (old_x + 30))
                data->player.turn_dir = +1;
        }

        last_click_time = current_time;
        update(data);
        draw_window(data);
    }
    return (0);
}




