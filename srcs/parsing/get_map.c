/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicedo <mvicedo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 11:47:25 by mvicedo           #+#    #+#             */
/*   Updated: 2023/07/06 15:04:41 by mvicedo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	get_map(t_data *data, t_file *file)
{
	int	index;
	int	j;

	index = 0;
	while (file->content[index])
	{
		j = 0;
		while (ft_isspace(file->content[index][j]))
			j++;
		if (file->content[index][j] == '0' || file->content[index][j] == '1')
			break ;
		index++;
	}
	if (ft_fill_map(&data->map, file->content, index, 0, 0))
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

int	ft_fill_map(t_map *map, char **map_file, int index, int i, int j)
{
	//int		len;
	
	printf("index = %d\n", index);
	map->map = (char **)malloc((map->height + 1) * sizeof(char *));
	if (!map->map)
		return (1);
	j = 0;
	while (map_file[index])
	{
		i = 0;
		//len = ft_strlen(map_file[index]);
		//printf("len fill map = %d\n", len);
		map->map[j] = (char *)malloc((map->width + 1) * sizeof(char));
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
