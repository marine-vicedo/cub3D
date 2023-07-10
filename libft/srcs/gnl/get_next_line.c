/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicedo <mvicedo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 12:20:51 by mvicedo           #+#    #+#             */
/*   Updated: 2023/07/10 12:51:20 by mvicedo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_search_newline(char *s)
{
	unsigned int	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_getline(char *stash)
{
	char	*line;
	int		i;

	i = 0;
	if (!stash || stash[0] == '\0')
		return (NULL);
	line = malloc(sizeof(char) * ft_strlen(stash) + 1);
	if (!line)
		return (NULL);
	while (stash[i] && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*ft_save_stash(char *stash)
{
	char	*save;
	int		i;
	int		j;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\0')
		return (free (stash), NULL);
	if (stash[i])
		i++;
	save = malloc(sizeof(char) * ((ft_strlen(stash + i) + 1)));
	if (!save)
	{
		free (stash);
		return (NULL);
	}
	j = 0;
	while (stash[i] != '\0')
		save[j++] = stash[i++];
	save[j] = '\0';
	free (stash);
	return (save);
}

char	*get_next_line(int fd)
{
	static char		*stash;
	char			*line;
	char			*buffer;
	int				i_read;

	i_read = 1;
	buffer = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || (read(fd, 0, 0) == -1))
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	while (i_read > 0 && (ft_search_newline(stash) == 0))
	{
		i_read = read(fd, buffer, BUFFER_SIZE);
		if (i_read == -1)
			return (NULL);
		buffer[i_read] = '\0';
		stash = ft_strjoin_gnl(stash, buffer);
	}
	free (buffer);
	line = ft_getline(stash);
	stash = ft_save_stash(stash);
	return (line);
}
