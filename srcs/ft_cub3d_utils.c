/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myvh <myvh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 20:39:50 by myvh              #+#    #+#             */
/*   Updated: 2023/05/09 20:58:35 by myvh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float		ft_lim_alpha(float alpha)
{
	if (alpha > 2 * PI)
		alpha -= 2 * PI;
	else if (alpha <= 0)
		alpha += 2 * PI;
	return (alpha);
}

float		ft_dist(float x_w, float y_w, float x0, float y0)
{
	float	dist;

	dist = sqrt((x_w - x0) * (x_w - x0) + (y_w - y0) * (y_w - y0));
	return (dist);
}

int			it_is_a_wall(float x, float y, t_env *env)
{
	int		x_ent;
	int		y_ent;

	x_ent = (int)(floor(x));
	y_ent = (int)(floor(y));
	if (y_ent < 0 || y_ent + 1 > env->size_y)
		return (1);
	if (x_ent < 0 || x_ent + 1 > env->size_line[y_ent])
		return (1);
	if (!env->map[y_ent][x_ent])
		return (1);
	else
	{
		if (env->map[y_ent][x_ent] == '1')
			return (0);
	}
	return (-1);
}

int			ft_error(char *error)
{
	write(1, error, ft_strlen(error));
	return (-1);
}

int			ft_check_color(int r, int g, int b)
{
	if (r < 0 || r > 255)
		return (-1);
	if (g < 0 || g > 255)
		return (-1);
	if (b < 0 || b > 255)
		return (-1);
	return (0);
}
