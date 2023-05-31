/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicedo <mvicedo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 12:20:47 by mvicedo           #+#    #+#             */
/*   Updated: 2023/05/31 15:01:04 by mvicedo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin_gnl(char *stash, char *buffer)
{
	char	*str;
	int		i;
	int		j;
	int		len;

	i = 0;
	len = ft_strlen(stash) + ft_strlen(buffer);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	while (stash && stash[i] != '\0')
	{
		str[i] = stash[i];
		i++;
	}
	j = 0;
	while (buffer && buffer[j] != '\0')
		str[i++] = buffer[j++];
	str[i] = '\0';
	free (stash);
	return (str);
}
