/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myvh <myvh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 20:40:20 by myvh              #+#    #+#             */
/*   Updated: 2023/05/09 20:58:35 by myvh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_wall		*ft_find_wall_dist(t_env *env, float alpha)
{
	t_wall	*wall_h;
	t_wall	*wall_v;

	wall_h = check_horizontal(env, alpha);
	wall_v = check_vertical(env, alpha);
	if (wall_h->dist < wall_v->dist)
	{
		free(wall_v);
		wall_h->orientation = ft_orient_wall(alpha, 'y');
		return (wall_h);
	}
	else
	{
		free(wall_h);
		wall_v->orientation = ft_orient_wall(alpha, 'x');
		return (wall_v);
	}
}

t_wall		*check_horizontal(t_env *env, float alpha)
{
	t_wall	*w;
	float	cot;
	float	delta_x;
	float	delta_y;

	cot = (1) / tan(alpha);
	w = ft_init_wall();
	if (alpha != 0)
	{
		if (alpha < PI)
		{
			w->y_wall = floor(env->pos.y) - 0.001;
			delta_y = -1;
		}
		if (alpha > PI)
		{
			w->y_wall = floor(env->pos.y) + 1;
			delta_y = 1;
		}
		w->x_wall = (env->pos.y - w->y_wall) * cot + env->pos.x;
		delta_x = -delta_y * cot;
		w = find_next_wall(env, w, delta_x, delta_y);
	}
	return (w);
}

t_wall		*find_next_wall(t_env *env, t_wall *w, float d_x, float d_y)
{
	int		dof;
	int		size;

	dof = 0;
	if (d_y == 1 || d_y == -1)
		size = env->size_y;
	else
		size = env->size_x;
	while (dof < size)
	{
		if (!(it_is_a_wall(w->x_wall, w->y_wall, env)))
		{
			dof = size;
			w->wall = env->map[(int)(floor(w->y_wall))]
				[(int)(floor(w->x_wall))] - 48;
			w->dist = ft_dist(w->x_wall, w->y_wall, env->pos.x, env->pos.y);
		}
		else
		{
			w->x_wall += d_x;
			w->y_wall += d_y;
			dof += 1;
		}
	}
	return (w);
}

t_wall		*check_vertical(t_env *env, float alpha)
{
	t_wall	*w;
	float	tang;
	float	delta_x;
	float	delta_y;

	tang = -tan(alpha);
	w = ft_init_wall();
	if (alpha != 3 * PI / 2)
	{
		if (alpha > PI / 2 && alpha < 3 * PI / 2)
		{
			w->x_wall = floor(env->pos.x) - 0.001;
			delta_x = -1;
		}
		if (alpha < PI / 2 || alpha > 3 * PI / 2)
		{
			w->x_wall = floor(env->pos.x) + 1;
			delta_x = 1;
		}
		w->y_wall = (w->x_wall - env->pos.x) * tang + env->pos.y;
		delta_y = delta_x * tang;
		w = find_next_wall(env, w, delta_x, delta_y);
	}
	return (w);
}

char		ft_orient_wall(float alpha, char c)
{
	if (c == 'x')
	{
		if (alpha > PI / 2 && alpha <= 3 * PI / 2)
			return ('W');
		else
			return ('E');
	}
	else if (c == 'y')
	{
		if (alpha > 0 && alpha < PI)
			return ('N');
		else
			return ('S');
	}
	else
		return (-1);
}
