/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicedo <mvicedo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:45:06 by mvicedo           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/05/31 14:45:08 by mvicedo          ###   ########.fr       */
=======
/*   Updated: 2023/06/13 16:11:00 by mvicedo          ###   ########.fr       */
>>>>>>> Marine
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

<<<<<<< HEAD
int	ft_count_lines(char *av)
=======
int	ft_count_lines(t_data *data, char *av)
>>>>>>> Marine
{
	int			fd;
	long int	i;
	char		*line;

	i = 0;
	fd = open(av, O_RDONLY);
	if (fd < 0)
<<<<<<< HEAD
		ft_fd_error();
	line = get_next_line(fd);
	if (!line)
		ft_str_error();
=======
		exit_clean(data, strerror(errno), 0);
	line = get_next_line(fd);
	if (!line)
		exit_clean(data, "Empty map file", FREE);
>>>>>>> Marine
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		i++;
	}
	close(fd);
	if (i > INT_MAX)
		i = INT_MAX;
	return ((int)i);
}

<<<<<<< HEAD
void	ft_copy_fileinfo(char *av, t_file *file)
=======
void	ft_copy_fileinfo(char *av, t_data *data)
>>>>>>> Marine
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	fd = open(av, O_RDONLY);
	if (fd < 0)
<<<<<<< HEAD
		ft_fd_error();
	line = get_next_line(fd);
	if (!line)
		ft_str_error();
	file->content = malloc(sizeof(char *) * (file->height + 1));
	if (!file->content)
		return ;
	while (line)
	{
		file->content[i++] = ft_strdup_no_nl(line);
		free(line);
		line = get_next_line(fd);
	}
	file->content[i] = NULL;
=======
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
>>>>>>> Marine
	free(line);
	close (fd);
}

int	ft_parsing_map(char *av, t_data *data)
{
<<<<<<< HEAD
	data->file.height = ft_count_lines(av);
=======
	data->file.height = ft_count_lines(data, av);
>>>>>>> Marine
	if (data->file.height == INT_MAX)
		return (exit_clean(data, ERR_FILE_TOO_BIG, 0));
	if (data->file.height < 5)
		return (exit_clean(data, ERR_FILE_TOO_SMALL, 0));
<<<<<<< HEAD
	ft_copy_fileinfo(av, &data->file);
	if (ft_file_content(data, &data->file))
		return (ft_free_data(data), 1);
	if (ft_check_walls(&data->map, data->map.map))
	{
		return(exit_clean(data, ERR_MAP_WALLS, FREE));
		//err_msg(ERR_MAP_WALLS, 1);
		//return (ft_free_map(data->map.map), 1);
	}
	if (ft_check_empty_space(&data->map, data->map.map))
	{
		return(exit_clean(data, ERR_MAP_WALLS, FREE));
		// err_msg(ERR_MAP_WALLS, 1);
		// return (ft_free_map(data->map.map), 1);
	}
=======
	ft_copy_fileinfo(av, data);
	if (ft_file_content(data, &data->file))
		return (exit_clean(data, NULL, FREE));
	if (ft_check_walls(&data->map, data->map.map))
		return(exit_clean(data, ERR_MAP_WALLS, FREE));
	if (ft_check_empty_space(&data->map, data->map.map))
		return(exit_clean(data, ERR_MAP_WALLS, FREE));
>>>>>>> Marine
	return (0);
}