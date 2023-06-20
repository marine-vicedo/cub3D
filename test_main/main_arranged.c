int	main_loop(t_data *data)
{
	updata(data);
	paint_floor(data);
	draw_minimap(data);
	paint_img(data);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;
	
	if (ac == 2)
	{
		ft_parsing(&data, av[1]);
		start_game(&data);
		mlx_hook(&data.win_mini, 2, 1L << 0, handle_keypress, &data);
		//mlx_hook(data.win_mini, 3, 1L << 0, handle_keyrelease, &data);
		mlx_hook(&data.win_mini, 17, 1L << 0, exit_game, &data);
		mlx_hook(&data.win, 17, 1L << 0, exit_game, &data);
		//mlx_loop_hook(data.mlx, &main_loop, &data);
		mlx_loop(data.mlx);
	}
	else
		exit(0);
}