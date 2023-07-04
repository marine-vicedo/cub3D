/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicedo <mvicedo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 14:13:20 by mvicedo           #+#    #+#             */
/*   Updated: 2023/07/04 15:03:00 by mvicedo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub3D.h"

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

void	ft_filename_check(t_data *data, char *av)
{
	int	i;

	i = 0;
	if (!av)
		return ;
	while (av[i])
		i++;
	if (i <= 4)
		exit_clean(data, ERR_FILE_NOT_CUB, 0);
	i = i - 4;
	if (av[i] != '.' || av[i + 1] != 'c' || av[i + 2] != 'u' \
	|| av[i + 3] != 'b')
		exit_clean(data, ERR_FILE_NOT_CUB, 0);
}

void	ft_parsing(t_data *data, char *av)
{
	ft_filename_check(data, av);
	ft_init_data(data);
	ft_parsing_map(av, data);
}
