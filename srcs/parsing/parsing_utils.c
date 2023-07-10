/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicedo <mvicedo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 11:50:31 by mvicedo           #+#    #+#             */
/*   Updated: 2023/07/10 18:11:55 by mvicedo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_isspace(char c)
{
	if (c == ' ')
		return (1);
	return (0);
}

int	ft_strlen_m(const char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

char	*ft_strdup_no_nl(const char *s)
{
	int		i;
	int		len;
	char	*dest;

	i = 0;
	len = ft_strlen_m((char *)s);
	dest = malloc(sizeof(char) * (len + 1));
	if (dest == 0)
		return (NULL);
	while (s[i] && s[i] != '\n')
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
