/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_colors_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicedo <mvicedo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:45:18 by mvicedo           #+#    #+#             */
/*   Updated: 2023/07/06 13:35:01 by mvicedo          ###   ########.fr       */
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
		return (NULL);
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
		return (err_msg(ERR_FILE_NOT_XPM), 1);
	i = i - 4;
	if (path[i] != '.' || path[i + 1] != 'x' || path[i + 2] != 'p' \
	|| path[i + 3] != 'm')
		return (err_msg(ERR_FILE_NOT_XPM), 1);
	return (0);
}

int	check_format_numbers(char *str)
{
	int	i;

	i = 0;
	if (!ft_isdigit(*str))
		return (err_msg("rgb digit error"), 1);
	while (*str)
	{
		if (*str == ',')
		{
			i++;
			str++;
			while (ft_isspace(*str))
				str++;
		}
		if (!ft_isdigit(*str))
			return (err_msg("Wrong rgb digit format"), 1);
		str++;
	}
	if (i != 2)
		return (err_msg("Missing rgb color"), 1);
	return (0);
}

int	set_rgb(char **str)
{
	int	rt;

	rt = ft_atoi(*str);
	while (ft_isdigit(**str))
		(*str)++;
	while ((**str) && (ft_strncmp(",", (*str), 1) == 0 || ft_isspace(**str)))
		(*str)++;
	return (rt);
}
