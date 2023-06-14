/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaimait <pmaimait@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:55:16 by mvicedo           #+#    #+#             */
/*   Updated: 2023/06/14 14:03:56 by pmaimait         ###   ########.fr       */
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
			return (err_msg("Map argv error"), 1);
		else if (c == 'W' || c == 'N' || c == 'S' || c == 'E')
		{
			if (p->status != 0)
				return (err_msg("More than one player"), 1);
			p->status = set_player_dir(c);
		}
		i++;
	}
	if (data->map.width < i + space)
		data->map.width = i + space;// a supprimer
	//printf("%d\n", data->map.width);
	// if (map->start == 0)
	// 	map->start = map->mcount;
	// printf("%d\n", map->mcount);
	return (0);
}

int	free_map(t_map *map, int j)
{
	int k;

	k = 0;
	while (k < j)
		free(map->map[k++]);
	free(map->map);
	return (1);
}

int	ft_fill_map(t_map *map, char **map_file, int index)
{
	int		i;
	int		j;
	map->map = (char **)malloc((map->height + 1) * sizeof(char *));
	if (!map->map)
		return (1);
	j = 0;
	while (map_file[index])
	{
		i = 0;
		map->map[j] = (char *)malloc((ft_strlen(map_file[index]) + 1) * sizeof(char));
		if (!map->map[j])
			free_map(map, j);
		while (map_file[index][i])
		{
			map->map[j][i] = map_file[index][i];
			i++;
		}
		map->map[j][i] = '\0';
		index++;
		j++;
	}
	map->map[j] = NULL;
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
	if (check_player_pos(str[0]))
		return (err_msg(ERR_MAP_WALLS), 1);
	return (0);
}