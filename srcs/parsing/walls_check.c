/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicedo <mvicedo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 13:04:35 by mvicedo           #+#    #+#             */
<<<<<<< HEAD:srcs/parsing/parsing5.c
<<<<<<< HEAD
/*   Updated: 2023/05/30 19:02:10 by mvicedo          ###   ########.fr       */
=======
/*   Updated: 2023/06/13 16:31:50 by mvicedo          ###   ########.fr       */
>>>>>>> Marine
=======
/*   Updated: 2023/06/14 13:19:49 by mvicedo          ###   ########.fr       */
>>>>>>> Marine:srcs/parsing/walls_check.c
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

<<<<<<< HEAD:srcs/parsing/parsing5.c
<<<<<<< HEAD
=======
int check_player_pos(int c)
=======
int	check_player_pos(int c)
>>>>>>> Marine:srcs/parsing/walls_check.c
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	return (0);
}

>>>>>>> Marine
static int	check_top_bottom(char **map, int i, int j)
{
	if (!map || !map[i] || !map[i][j])
		return (1);
	while (ft_isspace(map[i][j]))
		j++;
	while (map[i][j])
	{
<<<<<<< HEAD
		if (map[i][j] == '0')
=======
		if (map[i][j] == '0' || check_player_pos(map[i][j]))
>>>>>>> Marine
			return (1);
		j++;
	}
	return (0);
}

int	ft_check_walls(t_map *map, char **map_m)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;

	if (check_top_bottom(map_m, i, j))
		return (1);
	i = 1;
	while (i < (map->height - 1))
	{
		j = 0;
		len = ft_strlen(map_m[i]) - 1;
		while (ft_isspace(map_m[i][j]))
			j++;
		if (map_m[i][j] == '0' || map_m[i][len] == '0')
			return (1);
<<<<<<< HEAD
=======
		if (check_player_pos(map_m[i][0]) || check_player_pos(map_m[i][len]))
			return (1);
>>>>>>> Marine
		i++;
	}
	if (check_top_bottom(map_m, i, j))
		return (1);
	return (0);
}

int	ft_check_space_around(char **map_m, int i, int j)
{
	if (map_m[i][j - 1] == ' ' || (map_m[i][j + 1] && map_m[i][j + 1] == ' '))
		return (1);
	if (map_m[i - 1][j] == ' ' || (map_m[i + 1] && map_m[i + 1][j] == ' '))
		return (1);
	return (0);
}

int	ft_check_empty_space(t_map *map, char **map_m)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		len = ft_strlen(map_m[i]);
		while (j < len)
		{
			while (ft_isspace(map_m[i][j]))
				j++;
			if (map_m[i][j] == '0')
				if (ft_check_space_around(map_m, i, j))
					return (1);
			j++;
		}
		i++;
	}
	return (0);
}