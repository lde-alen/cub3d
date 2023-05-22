/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_wall.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myvh <myvh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 20:40:45 by myvh              #+#    #+#             */
/*   Updated: 2023/05/09 20:58:35 by myvh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float		*ft_printf_wall(t_env *env)
{
	t_wall			*w;
	float			*dist;
	t_print_wall	p;

	p.alpha = env->pos.dir + (PI / 4);
	p.x = 0;
	p.x_ecart = 2;
	if (!(dist = malloc(sizeof(float) * env->init.x_res)))
		return (NULL);
	while (p.alpha > env->pos.dir - (PI / 4) && p.x < env->init.x_res)
	{
		w = ft_find_wall_dist(env, ft_lim_alpha(p.alpha));
		p.x_ecart = env->init.x_res / 2 * (1 + tan(env->pos.dir - p.alpha));
		while (p.x <= p.x_ecart && p.x < env->init.x_res)
		{
			dist[p.x++] = (cos(p.alpha - env->pos.dir) * w->dist);
			ft_print_column(w, p.x, env, p.alpha);
		}
		free(w);
		p.alpha -= (PI / env->init.x_res);
	}
	return (dist);
}

void		ft_print_column(t_wall *w, int x, t_env *env, float alpha)
{
	int		nb_pixel;
	int		y;
	int		or;
	t_text	tex;

	or = ft_find_color(w);
	nb_pixel = ((float)env->init.y_res * 0.5) / (cos(alpha - env->pos.dir)
		* w->dist);
	y = round((env->init.y_res - nb_pixel) * env->pos.z / 4);
	if (y < 0)
		y = 0;
	tex.x = ft_find_x_text(env, w, or);
	while (y < round((env->init.y_res - nb_pixel) * (env->pos.z - 4)
		/ 4 + env->init.y_res) && x <= env->init.x_res && y < env->init.y_res)
	{
		tex.d_y = y * 256 - env->init.y_res * 128 + nb_pixel * 128;
		tex.y = ((tex.d_y * env->tex[or].height) / nb_pixel) / 256;
		ft_mlx_pixel_put(env->mlx.img, x, y,
			ft_mlx_get_color(env->tex[or], tex.x, (int)tex.y));
		y++;
	}
}

int			ft_find_x_text(t_env *env, t_wall *w, int or)
{
	int		text_x;
	float	x0;

	if (w->orientation == 'N' || w->orientation == 'S')
		x0 = w->x_wall - floor(w->x_wall);
	else
		x0 = w->y_wall - floor(w->y_wall);
	text_x = round(x0 * env->tex[or].width);
	return (text_x);
}

int			ft_find_color(t_wall *w)
{
	if (w->wall == 2)
		return (4);
	if (w->orientation == 'N')
		return (0);
	else if (w->orientation == 'W')
		return (2);
	else if (w->orientation == 'E')
		return (3);
	else if (w->orientation == 'S')
		return (1);
	return (0);
}

float		ft_init_pos(float pos)
{
	float retur;

	retur = pos - floor(pos);
	if (retur == 0)
		return (1);
	return (retur);
}
