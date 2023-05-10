/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprite_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myvh <myvh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 20:41:47 by myvh              #+#    #+#             */
/*   Updated: 2023/05/09 20:58:35 by myvh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		ft_sort_sprite(t_env *env)
{
	int		i;
	t_sp	tmp;

	i = -1;
	while (++i < env->sprite.nb - 1)
	{
		if (env->sprite.sp[i + 1].d > env->sprite.sp[i].d)
		{
			tmp = env->sprite.sp[i + 1];
			env->sprite.sp[i + 1] = env->sprite.sp[i];
			env->sprite.sp[i] = tmp;
			i = -1;
		}
	}
}

char		*ft_sprite(t_env *env)
{
	int		i;
	int		j;
	int		k;

	j = 0;
	k = 0;
	if (!(env->sprite.sp = malloc(sizeof(t_sp) * env->sprite.nb)))
		return ("Error\n Malloc of sprite");
	while (j < env->size_y && k < env->sprite.nb)
	{
		i = 0;
		while (env->map[j][i])
		{
			if (env->map[j][i] == '2')
			{
				env->sprite.sp[k].x = (float)i + 0.5;
				env->sprite.sp[k].y = (float)j + 0.5;
				k++;
			}
			i++;
		}
		j++;
	}
	return (NULL);
}

int			field_of_view(t_env *env, float alpha)
{
	float ang;

	ang = PI / 3;
	if (alpha <= env->pos.dir + ang && alpha >= env->pos.dir - ang)
		return (1);
	if (alpha <= env->pos.dir + ang - 2 * PI)
		return (1);
	if (alpha >= env->pos.dir - ang + 2 * PI)
		return (1);
	return (0);
}

float		angle(float alpha, float beta)
{
	if (beta == 0 && (int)(alpha / PI * 180) == 360)
		return (alpha - beta - 2 * PI);
	if (alpha >= 0 && alpha <= PI / 2 && beta >= 3 * PI / 2)
		return (alpha - beta + 2 * PI);
	if (alpha >= 3 * PI / 2 && alpha < 2 * PI && beta <= PI / 2)
		return (alpha - beta - 2 * PI);
	return (alpha - beta);
}
