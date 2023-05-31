/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicedo <mvicedo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 15:29:33 by pmaimait          #+#    #+#             */
/*   Updated: 2023/05/31 16:50:45 by mvicedo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub3D.h"


int	render(t_data *data)
{
	draw_minimap(data);
	return (0);
}

void	ft_fd_error(void)
{
	printf("Error : %s\n", strerror(errno));
	exit(EXIT_FAILURE);
}

void	ft_str_error(void)
{
	printf("Error : Empty map file\n");
	exit(EXIT_FAILURE);
}

void	ft_init_data(t_data *data)
{
	data->file.line_count = 0;
	data->file.content = NULL;
	data->file.height = 0;
	data->file.width = 0;
	data->file.north = NULL;
	data->file.south = NULL;
	data->file.west = NULL;
	data->file.east = NULL;
	data->file.floor = -1;
	data->file.ceiling = -1;
	data->file.flag = 0;
	data->player.status = 0;
	data->map.map = NULL;
	data->map.height = 0;
	data->map.width = 0;
}

void	ft_filename_check(char *av)
{
	int	i;

	i = 0;
	if (!av)
		return ;
	while (av[i])
		i++;
	if (i <= 4)
	{
		err_msg(ERR_FILE_NOT_CUB);
		exit(EXIT_FAILURE);
	}
	i = i - 4;
	if (av[i] != '.' || av[i + 1] != 'c' || av[i + 2] != 'u' \
	|| av[i + 3] != 'b')
	{
		err_msg(ERR_FILE_NOT_CUB);
		exit(EXIT_FAILURE);
	}
}

void	ft_parsing(t_data *data, char *av)
{
	ft_filename_check(av);
	ft_init_data(data);
	ft_parsing_map(av, data);
}

int main(int ac, char **av)
{
	t_data	*data;
	if (ac != 2)
		return (printf("Error\nCub3D need one argument (ex : map.cub)\n"), 1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	ft_parsing(data, av[1]);
	data->mlx= mlx_init();
	if (data->mlx== NULL || ac != 2)
		return (1);
	init_img(data);
	get_position_player(data);
	
    data->win = mlx_new_window(data->mlx, 960, 600, "cub3D");
	data->win_mini = mlx_new_window(data->mlx, (data->map.width * TILE_SIZE), (data->map.height * TILE_SIZE), "mini_map");
	if (data->win_mini == NULL || data->win == NULL)
	{
		free(data->win_mini);
		free(data->win);
		return (1);
	}
	init_player(data);
	draw_minimap(data);
	updata(data);

	
	
	/* Setup hooks */ 
	//mlx_loop_hook(data->mlx, &render, data);
	mlx_hook(data->win_mini, 2, 1L << 0, &handle_keypress, data);
	//mlx_hook(data->win_mini, 3, 1L << 0, &handle_keyrelease, data);
	mlx_hook(data->win_mini, 17, 1L << 0, &exit_game, data);
	mlx_loop(data->mlx);

	/* we will exit the loop if there's no window left, and execute this code */
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	free(data);
	return (0);
}

