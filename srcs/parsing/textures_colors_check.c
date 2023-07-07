/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_colors_check.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicedo <mvicedo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:45:10 by mvicedo           #+#    #+#             */
/*   Updated: 2023/07/07 13:53:37 by mvicedo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_color_check(t_file *file, char *str, char c)
{
	t_rgb	rgb;

	str += 2;
	while (ft_isspace(*str))
		str++;
	if (check_format_numbers(str))
		return (1);
	rgb.r = set_rgb(&str);
	rgb.g = set_rgb(&str);
	rgb.b = set_rgb(&str);
	if (!(rgb.r >= 0 && rgb.r <= 255) || !(rgb.g >= 0 && rgb.g <= 255)
		|| !(rgb.b >= 0 && rgb.b <= 255))
		return (err_msg("Invalid RGB value (min: 0, max: 255)"), 1);
	if (c == 'F' && file->floor == -1)
		file->floor = (rgb.r << 16 | rgb.g << 8 | rgb.b);
	else if (c == 'C' && file->ceiling == -1)
		file->ceiling = (rgb.r << 16 | rgb.g << 8 | rgb.b);
	else
		err_msg("double F or C keyword error");
	return (0);
}

int	ft_direction_check(t_file *file, char *str)
{
	char	*path;

	path = ft_direction_path(str);
	if (!path)
		return ((err_msg("Invalid direction texture"), 1));
	if (ft_is_xpm_file(path))
		return (free(path), 1);
	if (str[0] == 'N' && !file->north)
		file->north = path;
	else if (str[0] == 'S' && !file->south)
		file->south = path;
	else if (str[0] == 'W' && !file->west)
		file->west = path;
	else if (str[0] == 'E' && !file->east)
		file->east = path;
	else
		return (err_msg("Duplicate texture(s)"), free(path), 1);//free direction
	return (0);
}

static int	check_valid_characters(char *str)
{
	if (*str != ' ' && *str != '0' && *str != '1' && *str != 'W'
		&& *str != 'N' && *str != 'S' && *str != 'E'
		&& *str != 'F' && *str != 'C')
		return (1);
	return (0);
}

int	ft_check_fileinfo(t_data *data, t_file *file, char *str)
{
	int	space;

	space = 0;
	while (ft_isspace(*str))
	{
		str++;
		space++;
	}
	if (!ft_strncmp("NO ", str, 3) || !ft_strncmp("SO ", str, 3)
		|| !ft_strncmp("WE ", str, 3) || !ft_strncmp("EA ", str, 3))
		return (ft_direction_check(file, str));
	else if (!ft_strncmp("F ", str, 2) || !ft_strncmp("C ", str, 2))
		return (ft_color_check(file, str, str[0]));
	else if (str[0] == '\0' && file->flag != 0)
		return (err_msg("Empty line in map descriptor"), 1);
	else if (ft_check_mapfile(data, file, str, space))
		return (1);
	while (*str)
	{
		if (check_valid_characters(str))
			return (err_msg("Invalid character in the map"), 1);
		str++;
	}
	return (0);
}
