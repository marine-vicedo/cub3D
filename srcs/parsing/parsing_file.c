/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicedo <mvicedo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:45:06 by mvicedo           #+#    #+#             */
/*   Updated: 2023/07/10 18:07:38 by mvicedo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_print_map(char **tab)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tab[i] != NULL)
	{
		while (tab[i][j] != '\0')
		{
			write(1, &tab[i][j], 1);
			j++;
		}
		write(1, "\n", 1);
		j = 0;
		i++;
	}
	write(1, "\n", 1);
}

int	ft_count_lines(t_data *data, char *av)
{
	int			fd;
	long int	i;
	char		*line;

	i = 0;
	fd = open(av, O_RDONLY);
	if (fd < 0)
		exit_clean(data, strerror(errno), 0);
	line = get_next_line(fd);
	if (!line)
	{
		close(fd);
		exit_clean(data, "Empty map file", FREE);
	}
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		i++;
	}
	free(line);
	close(fd);
	if (i > INT_MAX)
		i = INT_MAX;
	return ((int)i);
}

void	ft_copy_fileinfo(char *av, t_data *data)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	fd = open(av, O_RDONLY);
	if (fd < 0)
		exit_clean(data, strerror(errno), 0);
	line = get_next_line(fd);
	if (!line)
		exit_clean(data, "Empty map file", 0);
	data->file.content = malloc(sizeof(char *) * (data->file.height + 1));
	if (!data->file.content)
		return ;
	while (line)
	{
		data->file.content[i] = ft_strdup_no_nl(line);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	data->file.content[i] = NULL;
	free(line);
	close(fd);
}

int	ft_file_content(t_data *data, t_file *file)
{
	int	i;

	i = 0;
	if (!file->content)
		return (1);
	while (file->content[i])
		if (ft_check_fileinfo(data, &data->file, file->content[i++]))
			return (1);
	if (!data->player.status)
		return (err_msg("No player"), 1);
	if (get_map(data, file))
		return (1);
	return (0);
}

int	ft_parsing_map(char *av, t_data *data)
{
	data->file.height = ft_count_lines(data, av);
	if (data->file.height == INT_MAX)
		return (exit_clean(data, ERR_FILE_TOO_BIG, 0));
	if (data->file.height < 5)
		return (exit_clean(data, ERR_FILE_TOO_SMALL, 0));
	ft_copy_fileinfo(av, data);
	if (ft_file_content(data, &data->file))
		return (exit_clean(data, NULL, FREE));
	if (ft_check_walls(&data->map, data->map.map))
		return (exit_clean(data, ERR_MAP_WALLS, FREE));
	if (ft_check_empty_space(&data->map, data->map.map))
		return (exit_clean(data, ERR_MAP_WALLS, FREE));
	return (0);
}
