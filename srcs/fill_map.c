/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 17:03:41 by lde-alen          #+#    #+#             */
/*   Updated: 2023/05/28 17:29:16 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	size_map(int fd)
{
	int		ret;
	int		size;
	char	*line;

	size = 1;
	ret = 1;
	line = NULL;
	while (ret == 1)
	{
		ret = get_next_line(fd, &line);
		if (line == NULL)
			return (-1);
		if (line[0] == '\n' || ft_strcmp(line, "") == 0)
		{
			size--;
			ret = 0;
		}
		line = ft_free(line);
		size++;
	}
	if (line)
		line = ft_free(line);
	line = NULL;
	return (size);
}

char	*fill_map(char *file, char **map, int size)
{
	int		fd;
	char	*line;
	int		i;
	int		ret;

	i = 0;
	ret = 1;
	fd = open(file, O_RDONLY);
	get_next_line(fd, &line);
	while (line[i] == ' ')
		i++;
	while (line[i] != '1' && ret == 1)
	{
		i = 0;
		line = ft_free(line);
		ret = get_next_line(fd, &line);
		while (line[i] == ' ')
			i++;
	}
	return (fill_line(fd, line, map, size));
}

char	*fill_line(int fd, char *line, char **map, int size)
{
	int		j;
	int		ret;

	j = 0;
	ret = 1;
	while (j < size)
	{
		map[j] = line;
		if (!map[j])
			return ("Error\nMalloc\n");
		ret = get_next_line(fd, &line);
		j++;
	}
	line = ft_free(line);
	map[j] = NULL;
	while (ret == 1)
	{
		ret = get_next_line(fd, &line);
		line = ft_free(line);
	}
	return (NULL);
}

int	orientation(char c)
{
	if (c == 'N')
		return (90);
	else if (c == 'E')
		return (0);
	else if (c == 'S')
		return (270);
	else if (c == 'W')
		return (180);
	else
		return (-1);
}

char	*check_zero(char **map, int i, int j, t_env *env)
{
	if (j - 1 < 0 || i - 1 < 0 || env->size_x == 0 || env->size_y == 0)
		return ("Error\nBad map.");
	if (j + 2 > env->size_y || i + 2 > env->size_x)
		return ("Error\nBad map.");
	if (!map[j - 1][i] || map[j - 1][i] == ' ')
		return ("Error\nBad map.");
	if (!map[j + 1][i] || map[j + 1][i] == ' ')
		return ("Error\nBad map.");
	if (!map[j][i - 1] || map[j][i - 1] == ' ')
		return ("Error\nBad map.");
	if (!map[j][i + 1] || map[j][i + 1] == ' ')
		return ("Error\nBad map.");
	return (NULL);
}
