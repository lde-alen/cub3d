/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhab       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 20:24:08 by lde-alen          #+#    #+#             */
/*   Updated: 2023/02/19 17:25:54 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_ext(char *map)
{
	int	size;
	int	i;

	i = 0;
	size = ft_strlen(map) - 1;
	if (map[size] == 'b' && map[size - 1] == 'u' && map[size - 2] == 'c'
		&& map[size - 3] == '.')
		return (1);
	return (0);
}

static int	check_file(char *path)
{
	int		fd;
	ssize_t	rd;
	char	*str;

	fd = open(path, O_RDONLY);
	rd = 4096;
	str = (char *)malloc(sizeof(char) * 4096);
	if (fd == -1)
		return (ft_putstr_fd("ERROR: Could not open the file\n", 2), 1);
	while (rd == 4096)
	{
		rd = read(fd, str, 4096);
		ft_putstr_fd(str, 1);
	}
	return (0);
}

int	ft_check_map(char *map)
{
	if (!check_ext(map))
		return (ft_putstr_fd("ERROR: Invalid file extension.\n", 2), 1);
	if (!check_file(map))
		return (1);
	return (0);
}
