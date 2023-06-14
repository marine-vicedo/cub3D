/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicedo <mvicedo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 11:50:22 by mvicedo           #+#    #+#             */
/*   Updated: 2023/06/14 13:22:55 by mvicedo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_free_map(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
}

void	ft_free_data(t_data *data)
{
	if (data->map.map)
		ft_free_map(data->map.map);
	if (data->file.content)
		ft_free_map(data->file.content);
	if (data->file.north)
		free(data->file.north);
	if (data->file.south)
		free(data->file.south);
	if (data->file.west)
		free(data->file.west);
	if (data->file.east)
		free(data->file.east);
}

void	err_msg(char *msg)
{
	ft_putstr_fd("cub3D: Error\n", 2);
	if (msg)
	{
		ft_putstr_fd(msg, 2);
		ft_putstr_fd("\n", 2);
	}
}

int	exit_clean(t_data *data, char *msg, int code)
{
	if (msg)
		err_msg(msg);
	if (code)
		ft_free_data(data);
	free(data);
	exit (1);
}
