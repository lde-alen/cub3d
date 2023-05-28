/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 13:41:31 by lde-alen          #+#    #+#             */
/*   Updated: 2023/05/28 17:30:11 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	convert_color(char *str)
{
	char	**s;
	int		color;
	int		i;

	i = 0;
	s = ft_split_str(str, " ,");
	if (s[4] != NULL || ft_strslen(s) != 4 || ft_strlen(s[0]) != 1)
		return (-1);
	if (check_color(ft_atoi(s[1]), ft_atoi(s[2]), ft_atoi(s[3])) == -1)
		return (-1);
	color = (ft_atoi(s[1]) * 256 + ft_atoi(s[2])) * 256 + ft_atoi(s[3]);
	while (s[i])
	{
		s[i] = ft_free(s[i]);
		i++;
	}
	s = ft_free(s);
	return (color);
}

char	*parse_color(t_map *init, char *line)
{
	int	color;

	color = convert_color(line);
	if (color == -1)
		return ("Error\nBad character in color\n");
	if (line[0] == 'F')
		init->floor = color;
	else
		init->ceiling = color;
	return (NULL);
}

char	*parse_texture(char *line, t_map *map)
{
	if (line[0] == 'N' && line[1] == 'O')
		map->texture[0] = ft_strtrim_path(&line[3], " ");
	else if (line[0] == 'S' && line[1] == 'O')
		map->texture[1] = ft_strtrim_path(&line[3], " ");
	else if (line[0] == 'W' && line[1] == 'E')
		map->texture[2] = ft_strtrim_path(&line[3], " ");
	else if (line[0] == 'E' && line[1] == 'A')
		map->texture[3] = ft_strtrim_path(&line[3], " ");
	else
		return ("Error\nNot a valid argument\n");
	return (NULL);
}

char	*parse(t_map *map_def, int *fd)
{
	int			ret;
	char		*l;
	int			i;
	char		*error;

	ret = 1;
	error = NULL;
	while (ret == 1 && error == NULL)
	{
		ret = get_next_line(*fd, &l);
		i = 0;
		while (l && l[i] == ' ')
			i++;
		if (l[i] == 'N' || l[i] == 'S' || l[i] == 'W' || l[i] == 'E')
			error = parse_texture(&l[i], map_def);
		else if (l[i] == 'F' || l[i] == 'C')
			error = parse_color(map_def, l + i);
		else if (l[i] == '1')
			ret = 0;
		else if (l [i] != '\0')
			error = "Invalid character in .cub\n";
		l = ft_free(l);
	}
	return (error);
}
