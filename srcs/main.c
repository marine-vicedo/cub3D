/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaimait <pmaimait@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 15:29:33 by pmaimait          #+#    #+#             */
/*   Updated: 2023/05/09 15:40:03 by pmaimait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub3D.h"


#define screenWidth 640
#define screenHeight 480


int main(int ac, char **av)
{
	/* double posX = 22, posY = 12;  //x and y start position
	double dirX = -1, dirY = 0; //initial direction vector
	double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane

	double time = 0; //time of current frame
	double oldTime = 0; //time of previous frame */
	t_data	data;

	data.mlx= mlx_init();
	if (data.mlx== NULL || ac != 2)
		return (1);
  init_img(&data);
  get_position_player(&data, av[1]);
  printf("position of player is (%d, %d)\n", (int)data.player.pos_x, (int)data.player.pos_y);
	data.win = mlx_new_window(data.mlx, (data.img.img_width * 50), (data.img.img_height * 50), "My test window!");
	if (data.win == NULL)
	{
		free(data.win);
		return (1);
	}

	// Set the color of the window to red
    int red = 255;
    int green = 0;
    int blue = 0;
    int color = (red << 16) + (green << 8) + blue;
    mlx_clear_window(data.mlx, data.win);
    mlx_pixel_put(data.mlx, data.win, (data.img.img_width * 50) / 2, (data.img.img_height * 50) / 2, color);

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