#include "cub3D.h"

int	ft_isspace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

// static int ft_strlen_no_nl(char *s)
// {
// 	int i;

// 	i = 0;
// 	while(s && s[i] && s[i] != '\n')
// 		i++;
// 	return (i);
// }

static int ft_strlen_m(const char *s)
{
	int i = 0;
	while (s && s[i])
		i++;
	return (i);
}

char	*ft_strdup_no_nl(const char *s)
{
	int	i;
	int	len;
	char	*dest;

	i = 0;
	// while(ft_isspace(*s))
	// 	s++;
	len = ft_strlen_m((char *)s);
	dest = malloc(sizeof(char) * (len));
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
		tab[i] = NULL;
		i++;
	}
	free(tab);
}

void	ft_free_data(t_data *data)
{
	if (data->map.map)
		ft_free_map(data->map.map);
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
