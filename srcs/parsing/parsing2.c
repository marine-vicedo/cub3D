/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicedo <mvicedo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:45:10 by mvicedo           #+#    #+#             */
/*   Updated: 2023/06/01 17:17:12 by mvicedo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*ft_direction_path(char *str)
{
	int		fd;
	char	*path;

	path = NULL;
	str += 2;
	while (ft_isspace(*str))
		str++;
	fd = open(str, O_RDONLY);
	if (fd < 0)
	{
		perror("Erreur lors de l'ouverture du fichier");
		return (NULL);
	}
	close(fd);
	path = ft_strdup(str);
	return (path);
}

int	ft_is_xpm_file(char *path)
{
	int	i;

	i = 0;
	if (!path)
		return (1);
	while (path[i])
		i++;
	if (i <= 4)
		return (printf("Error\nExtension file is not .xpm\n"), 1);
	i = i - 4;
	if (path[i] != '.' || path[i + 1] != 'x' || path[i + 2] != 'p' \
	|| path[i + 3] != 'm')
		return (printf("Error\nExtension file is not .xpm\n"), 1);
	return (0);
}

int	ft_direction_check(t_file *file, char *str)
{
	char	*path;

	path = ft_direction_path(str);
	if (!path)
		return ((printf("Error\nInvalid direction texture\n"), 1));
	if (ft_is_xpm_file(path))
		return (1);
	if (str[0] == 'N' && !file->north)
		file->north = path;
	else if (str[0] == 'S' && !file->south)
		file->south = path;
	else if (str[0] == 'W' && !file->west)
		file->west = path;
	else if (str[0] == 'E' && !file->east)
		file->east = path;
	else
		printf("Error\nDuplicate texture(s)");
	return (0);
}

int	ft_check_fileinfo(t_data *data, t_file *file, char *str)
{
	int	i;
	char *ptr;

	i = 0;
	ptr = ft_strdup(str);
	while (ft_isspace(*ptr))
		ptr++;
	if (!ft_strncmp("NO ", ptr, 3) || !ft_strncmp("SO ", ptr, 3)
		|| !ft_strncmp("WE ", ptr, 3) || !ft_strncmp("EA ", ptr, 3))
		return(ft_direction_check(file, ptr));
	else if (!ft_strncmp("F ", ptr, 2) || !ft_strncmp("C ", ptr, 2))
		return(ft_color_check(file, str, str[0]));
	else if (ptr[0] == '\0' && file->flag != 0)
		return (printf("Error\nEmpty line in map descriptor"), 1);
	else if (ft_check_mapfile(data, file, ptr))
		return (1);
	while(*ptr)
	{
		if (*ptr != ' ' && *ptr != '0' && *ptr != '1' && *ptr != 'W'
			&& *ptr != 'N' && *ptr != 'S' && *ptr != 'E' && *ptr != 'F' && *ptr != 'C')
		{
			return(printf("Error\nInvalid character in the map\n"), 1);
		}
		ptr++;
	}
	free(ptr);
	return (0);
}

int	get_map(t_data *data, t_file *file)
{
	int	i;

	i = 0;
	while (file->content[i])
	{
		// while (ft_isspace(*file->content[i]))
		// 	file->content[i]++;
		if (!ft_strncmp("NO ", file->content[i], 3) || !ft_strncmp("SO ", file->content[i], 3)
			|| !ft_strncmp("WE ", file->content[i], 3) || !ft_strncmp("EA ", file->content[i], 3))
			i++;
		else if (!ft_strncmp("F ", file->content[i], 2) || !ft_strncmp("C ", file->content[i], 2))
			i++;
		else if (file->content[i][0] == '\0')
			i++;
		else if (ft_isspace(file->content[i][0]) || file->content[i][0] == '0' || file->content[i][0] == '1')
			break;
	}
	if (ft_fill_map(&data->map, file->content, i))
		return (1);
	return (0);
}

int	ft_file_content(t_data *data, t_file *file)
{
	int	i;

	i = 0;
	if (!file->content)
		return (1);
	// while (file->content[i])
	// 	if (ft_check_fileinfo(data, &data->file, file->content[i++]))
	// 		return (1);
	// ft_print_map(data->file.content);
	// if (!data->player.status)
	// 	return (printf("No player\n"), 1);
	if (get_map(data, file))
			return (1);
	return (0);
}