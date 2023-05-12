/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parida <parida@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:07:48 by pmaimait          #+#    #+#             */
/*   Updated: 2023/05/12 23:04:01 by parida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub3D.h"

static char	*ft_strjoin_solong(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	if (s1)
	{
		while (s1[i])
			str[j++] = s1[i++];
		free(s1);
	}
	i = 0;
	while (s2[i])
		str[j++] = s2[i++];
	str[j] = '\0';
	return (str);
}

static int	ft_strlen_newline(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}

char	**read_map(t_data *data, char *map)
{
	int		fd;
	char	*line;
    char    *str;

	fd = open(map, O_RDONLY);
	if (fd <= 0)
	{
		free(data);
		printf("File open fail.\n");
	}
	data->map.height = 0;
	str = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		data->map.width = ft_strlen_newline(line);
		str = ft_strjoin_solong(str, line);
		free(line);
		data->map.height++;
	}
	close(fd);
	
    return (ft_split(str, '\n'));
}

void    get_position_player(t_data *data, char *map)
{
    t_player    *player;
    t_minimap       *minimap;
    int     i;
    int     j; 

    j = 0;
    player = &data->player;
    minimap = &data->minimap;
    minimap->map = read_map(data, map);
    while (j < data->map.height )
    {
        i = 0;
        while (i < data->map.width)
        {
			//printf("%c", minimap->map[j][i]);
            if (minimap->map[j][i] == 'P')
            {
                player->pos_x = i;
                player->pos_y = j;
            }
            i++;
        }
		//printf("\n");
        j++;
    }
}