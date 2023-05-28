/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 17:03:47 by lde-alen          #+#    #+#             */
/*   Updated: 2023/05/28 17:29:25 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_map	init_map_struct(void)
{
	t_map	map;

	map.fov = FOV;
	map.floor = -1;
	map.ceiling = -1;
	return (map);
}

t_position	init_position(void)
{
	t_position	pos;

	pos.x = 0;
	pos.y = 0;
	pos.dir = 0;
	pos.mk = 0;
	return (pos);
}

char	**init_map(int fd, char *file, int *size)
{
	char	**map;

	*size = size_map(fd);
	map = malloc((*size + 1) * sizeof(char *));
	if (!map)
		return (NULL);
	fill_map(file, map, *size);
	return (map);
}

t_key	init_key(void)
{
	t_key	key;

	key.a = 0;
	key.d = 0;
	key.s = 0;
	key.w = 0;
	key.r = 0;
	key.l = 0;
	key.u = 0;
	key.v = 0;
	return (key);
}
