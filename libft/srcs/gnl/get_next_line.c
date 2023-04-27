/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaimait <pmaimait@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:07:41 by pmaimait          #+#    #+#             */
/*   Updated: 2023/04/18 13:49:41 by pmaimait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line.h"

char	*ft_free(char *stash, char *buf)
{
	char	*to_free;

	to_free = ft_strjoin_gnl(stash, buf);
	free(stash);
	return (to_free);
}

char	*next_stash(char *stash)
{
	char	*new_stash;
	int		len;
	int		i;

	if (!stash || ft_strchr_gnl(stash, '\n') == NULL)
		return (free(stash), NULL);
	len = 0;
	while (stash[len] && stash[len] != '\n')
		len++;
	new_stash = malloc(sizeof(char) * (ft_strlen_gnl(stash) - len + 1));
	if (!new_stash)
		return (NULL);
	len++;
	i = 0;
	while (stash[len])
		new_stash[i++] = stash[len++];
	new_stash[i] = '\0';
	free(stash);
	return (new_stash);
}

char	*generate_line(char *stash)
{
	char	*line;
	int		i;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (ft_strchr_gnl(stash, '\n') == NULL)
		line = malloc(sizeof(char) * i + 1);
	else
		line = malloc(sizeof(char) * i + 2);
	if (!line)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*read_file(int fd, char *stash)
{
	char	*buf;
	int		read_size;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	read_size = 1;
	while (read_size != 0)
	{
		read_size = read(fd, buf, BUFFER_SIZE);
		if (read_size < 0 || (!stash && !read_size))
			return (free(buf), NULL);
		buf[read_size] = '\0';
		stash = ft_free(stash, buf);
		if (ft_strchr_gnl(buf, '\n'))
			break ;
	}
	free(buf);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	stash = read_file(fd, stash);
	if (!stash)
		return (free(stash), NULL);
	line = generate_line(stash);
	if (line[0] == '\0')
		return (free(stash), free(line), NULL);
	stash = next_stash(stash);
	return (line);
}
