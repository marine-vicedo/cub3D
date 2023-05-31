/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicedo <mvicedo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:45:18 by mvicedo           #+#    #+#             */
/*   Updated: 2023/05/29 13:38:38 by mvicedo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_format_numbers(char *str)
{
	int	i;

	i = 0;
	if (!ft_isdigit(*str))
		return (printf("rgb digit error\n"), 1);
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
			return (printf("rgb error\n"), 1);
		str++;
	}
	if (i != 2)
		return (printf("Error\nMissing rgb color\n"), 1);
	return (0);
}

int	set_rgb(char **str)
{
	int	rt;

	rt = ft_atoi(*str);
	// if (rt == 0)
	// 	(*str)++;
	while (ft_isdigit(**str))
		(*str)++;
	while ((**str) && (ft_strncmp(",", (*str), 1) == 0 || ft_isspace(**str)))
		(*str)++;
	return (rt);
}

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
		return (printf("Error\nInvalid RGB value (min: 0, max: 255)\n"), 1);
	if (c == 'F' && file->floor == -1)
		file->floor = (rgb.r << 16 | rgb.g << 8 | rgb.b);
	else if (c == 'C' && file->ceiling == -1)
		file->ceiling = (rgb.r << 16 | rgb.g << 8 | rgb.b);
	else
		printf("double F or C keyword error\n");
	return (0);
}