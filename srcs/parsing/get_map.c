/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicedo <mvicedo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 11:47:25 by mvicedo           #+#    #+#             */
/*   Updated: 2023/06/14 12:06:15 by mvicedo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	get_map(t_data *data, t_file *file)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (file->content[i])
	{
		while (ft_isspace(file->content[i][j]))
			j++;
		if (file->content[i][j] == '0' || file->content[i][j] == '1')
			break ;
		i++;
	}
	if (ft_fill_map(&data->map, file->content, i))
		return (1);
	return (0);
}

int	free_map(t_map *map, int j)
{
	int	k;

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
		map->map[j] = (char *)malloc
			((ft_strlen(map_file[index]) + 1) * sizeof(char));
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