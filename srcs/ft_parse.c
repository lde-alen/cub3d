/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myvh <myvh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 20:40:39 by myvh              #+#    #+#             */
/*   Updated: 2023/05/10 20:26:01 by myvh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char		*ft_parse(t_map *map_def, int *fd)
{
	int			ret;
	char		*line;
	int			i;
	char		*error;

	ret = 1;
	error = NULL;
	while (ret == 1 && error == NULL)
	{
		ret = get_next_line(*fd, &line);
		i = 0;
		while (line && line[i] == ' ')
			i++;
		if (line[i] == 'N' || line[i] == 'S' || line[i] == 'W' ||
				line[i] == 'E')
			error = ft_parse_texture(&line[i], map_def);
		else if (line[i] == 'F' || line[i] == 'C')
			error = ft_parse_color(map_def, line);
		else if (line[i] == '1')
			ret = 0;
		free(line);
		line = NULL;
	}
	return (error);
}

char		*ft_parse_color(t_map *init, char *line)
{
	int			color;

		color = ft_convert_color(line);
		if (color == -1)
			return ("Error\nBad character in color\n");
		if (line[0] == 'F')
			init->floor = color;
		else
			init->ceiling = color;
	return (NULL);
}

int			ft_convert_color(char *str)
{
	char	**s;
	int		color;
	int		j;

	j = -1;
	s = ft_split_str(str, " ,");
	if (s[4] != NULL || ft_strslen(s) != 4 || ft_strlen(s[0]) != 1)
		return (-1);
	if (ft_check_color(ft_atoi(s[1]), ft_atoi(s[2]), ft_atoi(s[3])) == -1)
		return (-1);
	color = (ft_atoi(s[1]) * 256 + ft_atoi(s[2])) * 256 + ft_atoi(s[3]);
	while (s[++j])
		free(s[j]);
	free(s);
	return (color);
}

char		*ft_parse_texture(char *line, t_map *map)
{
	if (line[0] == 'N' && line[1] == 'O')
		map->texture[0] = ft_strtrim_path(&line[3], " ");
	else if (line[0] == 'S' && line[1] == 'O')
		map->texture[1] = ft_strtrim_path(&line[3], " ");
	else if (line[0] == 'W' && line[1] == 'E')
		map->texture[2] = ft_strtrim_path(&line[3], " ");
	else if (line[0] == 'E' && line[1] == 'A')
		map->texture[3] = ft_strtrim_path(&line[3], " ");
	else if (line[0] == 'S' && line[1] == ' ')
		map->texture[4] = ft_strtrim_path(&line[2], " ");
	else
		return ("Not a valid argument\n");
	return (NULL);
}
