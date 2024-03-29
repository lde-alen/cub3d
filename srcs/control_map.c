/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 17:10:27 by lde-alen          #+#    #+#             */
/*   Updated: 2023/05/28 17:24:10 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_control_map(t_env *s)
{
	int	i;
	int	j;

	j = 0;
	while (s->map[j])
	{
		i = -1;
		while (s->map[j][++i])
		{
			if (s->map[j][i] == 'N' || s->map[j][i] == 'E'
				|| s->map[j][i] == 'W' || s->map[j][i] == 'S')
			{
				s->pos.x = i + 0.5;
				s->pos.y = j + 0.5;
				s->pos.dir = orientation(s->map[j][i]);
				s->map[j][i] = '0';
				s->pos.mk++;
			}
			else if (s->map[j][i] != '1' && s->map[j][i] != '0'
					&& s->map[j][i] != ' ')
				return ("Error\nBad character inside the map\n");
		}
		j++;
	}
	return (control_map(s->map, s));
}

char	*control_map(char **map, t_env *env)
{
	int		i;
	int		j;
	char	*error;

	j = -1;
	while (++j < env->size_y)
	{
		i = 0;
		while (map[j][i])
		{
			if (map[j][i] == '0')
			{
				error = check_zero(map, i, j, env);
				if (error != NULL)
					return (error);
			}
			i++;
		}
	}
	if (env->pos.mk != 1)
		return ("Error\nToo much or no perso.");
	return (NULL);
}
