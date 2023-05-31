#include "cub3D.h"

int	ft_isspace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

char	*ft_strdup_no_nl(const char *s)
{
	size_t	i;
	size_t	len;
	char	*dest;

	i = 0;
	len = ft_strlen((char *)s);
	dest = (char *)malloc ((len + 1) * sizeof(char));
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

void	ft_free_map(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	ft_free_data(t_data *data)
{
	printf("map->map : \n");
	if (data->map.map)
		ft_free_map(data->map.map);
	printf("\n\n\n\n\n");
	printf("file->content : \n");
	if (data->file.content)
		ft_free_map(data->file.content);
	if (data->file.north)
		free(data->file.north);
	if (data->file.south)
		free(data->file.south);
	if (data->file.west)
		free(data->file.west);
	if (data->file.east)
		free(data->file.east);
}

void	err_msg(char *msg)
{
	ft_putstr_fd("cub3D: Error\n", 2);
	if (msg)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(msg, 2);
		ft_putstr_fd("\n", 2);
	}
}

int exit_clean(t_data *data, char *msg, int code)
{
	if (msg)
		err_msg(msg);
	if (code)
		ft_free_data(data);
	return (1);
}
