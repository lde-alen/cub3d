/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myvh <myvh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 20:40:34 by myvh              #+#    #+#             */
/*   Updated: 2023/05/09 20:58:35 by myvh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		ft_incr_pos_lat(t_env *env, char sign)
{
	float ang;

	if (sign == 'l')
		ang = env->pos.dir + PI / 2;
	if (sign == 'r')
		ang = env->pos.dir - PI / 2;
	env->pos.speed = 0.1;
	env->pos.x += env->pos.speed * cos(ang);
	env->pos.y -= env->pos.speed * sin(ang);
	if (env->pos.x < 1.25 || env->pos.x > env->size_x - 1.25)
		env->pos.x -= env->pos.speed * cos(ang);
	if (env->pos.y < 1.25 || env->pos.y > env->size_y - 1.25)
		env->pos.y += env->pos.speed * sin(ang);
}

void		ft_move(t_env *env)
{
	float	*dist;

	if (env->key.w)
		env->pos = ft_incr_pos(env, 1);
	if (env->key.s)
		env->pos = ft_incr_pos(env, -1);
	if (env->key.l)
		env->pos.dir = ft_incr_ori(env->pos, 'l');
	if (env->key.r)
		env->pos.dir = ft_incr_ori(env->pos, 'r');
	if (env->key.a)
		ft_incr_pos_lat(env, 'l');
	if (env->key.d)
		ft_incr_pos_lat(env, 'r');
	ft_reset_opti(env->mlx.img.opti);
	if (!(dist = ft_printf_wall(env)))
		ft_quit_mlx(env);
	ft_surface_color(env);
	ft_printf_sprite(env, dist);
	free(dist);
	mlx_put_image_to_window(env->mlx.mlx, env->mlx.win, env->mlx.img.img, 0, 0);
}

float		ft_incr_ori(t_position pos, char dir)
{
	float	retur;
	float	incr;

	incr = PI / 32;
	if (dir == 'l')
		retur = pos.dir + incr;
	else
		retur = pos.dir - incr;
	if (retur > 2 * PI)
		retur -= 2 * PI;
	else if (retur <= 0)
		retur += 2 * PI;
	return (retur);
}

t_position	ft_incr_pos(t_env *env, int sign)
{
	env->pos.speed = 0.1;
	env->pos.x += sign * env->pos.speed * cos(env->pos.dir);
	env->pos.y -= sign * env->pos.speed * sin(env->pos.dir);
	if (env->pos.x < 1.25 || env->pos.x > env->size_x - 1.25)
		env->pos.x -= sign * env->pos.speed * cos(env->pos.dir);
	if (env->pos.y < 1.25 || env->pos.y > env->size_y - 1.25)
		env->pos.y += sign * env->pos.speed * sin(env->pos.dir);
	return (env->pos);
}

void		ft_reset_opti(char **opti)
{
	int	i;
	int	j;

	j = -1;
	while (opti[++j])
	{
		i = -1;
		while (opti[j][++i])
			opti[j][i] = '0';
	}
}
