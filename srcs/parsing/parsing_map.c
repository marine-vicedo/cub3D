/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicedo <mvicedo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:55:16 by mvicedo           #+#    #+#             */
/*   Updated: 2023/07/10 17:58:04 by mvicedo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	set_player_dir(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	return (0);
}

int	ft_is_valid_map(t_data *data, t_player *p, char *line, int space)
{
	int		i;
	char	c;

	i = 0;
	while (line[i])
	{
		c = line[i];
		if (!(c == ' ') && c != '0' && c != '1' && c != 'W'
			&& c != 'N' && c != 'S' && c != 'E')
			return (err_msg("Invalid char in the map"), 1);
		else if (c == 'W' || c == 'N' || c == 'S' || c == 'E')
		{
			if (p->status != 0)
				return (err_msg("More than one player"), 1);
			p->status = set_player_dir(c);
		}
		i++;
	}
	if (data->map.width < i + space)
		data->map.width = i + space;
	return (0);
}

int	ft_check_mapfile(t_data *data, t_file *file, char *str, int space)
{
	int	i;

	i = 0;
	if (str[i] == '0' || str[i] == '1')
	{
		data->map.height += 1;
		file->flag = 1;
		if (!file->north || !file->south || !file->west || !file->east
			|| (file->floor == -1) || (file->ceiling == -1))
			return (err_msg
				("Something missing or file order is wrong"), 1);
		if (ft_is_valid_map(data, &data->player, str, space))
			return (1);
	}
	else
		return (err_msg("Invalid character in the map"), 1);
	return (0);
}
