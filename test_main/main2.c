/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaimait <pmaimait@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 11:37:17 by pmaimait          #+#    #+#             */
/*   Updated: 2023/05/10 15:25:59 by pmaimait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

	// Set the color of the window to red
    int red = 255;
    int green = 0;
    int blue = 0;
    int color = (red << 16) + (green << 8) + blue;
    mlx_clear_window(data.mlx, data.win);
    mlx_pixel_put(data.mlx, data.win, SCWIDTH / 2, SCHEIGHT / 2, color);

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


int main()
{
    void *mlx_ptr = mlx_init();
    void *win_ptr = mlx_new_window(mlx_ptr, 500, 500, "My Window");
    void *img_ptr = mlx_new_image(mlx_ptr, 500, 500);
    char *img_data = mlx_get_data_addr(img_ptr, &bits_per_pixel, &size_line, &endian);

    // Set the color of pixel (x=100, y=100) to red
    int x = 100;
    int y = 100;
    int color = 0xFF0000; // Red color in hexadecimal format
    int pixel_index = (y * size_line) + (x * (bits_per_pixel / 8));
    *(int *)(img_data + pixel_index) = color;

    mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 0, 0);

    mlx_loop(mlx_ptr);
}