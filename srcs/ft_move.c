/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 20:40:34 by myvh              #+#    #+#             */
/*   Updated: 2023/05/28 13:40:43 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_incr_pos_lat(t_env *env, char sign)
{
	float	ang;

	if (sign == 'l')
		ang = env->pos.dir * DTOR + PI / 2;
	if (sign == 'r')
		ang = env->pos.dir * DTOR - PI / 2;
	env->pos.speed = 0.1;
	env->pos.x += env->pos.speed * cos(ang);
	env->pos.y -= env->pos.speed * sin(ang);
	if (env->pos.x < 1.25 || env->pos.x > env->size_x - 1.25)
		env->pos.x -= env->pos.speed * cos(ang);
	if (env->pos.y < 1.25 || env->pos.y > env->size_y - 1.25)
		env->pos.y += env->pos.speed * sin(ang);
}

void	ft_move(t_env *env)
{
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
	if (env->key.u)
		if (env->init.fov < 160)
			env->init.fov += 5;
	if (env->key.v)
		if (env->init.fov > 20)
			env->init.fov -= 5;
	ft_reset_opti(env->mlx.img.opti);
	raycasting(env);
	mlx_put_image_to_window(env->mlx.mlx, env->mlx.win, env->mlx.img.img, 0, 0);
}

int	ft_incr_ori(t_position pos, char dir)
{
	int	retur;
	int	incr;

	incr = 5;
	if (dir == 'l')
		retur = pos.dir + incr;
	else
		retur = pos.dir - incr;
	if (retur > 360)
		retur -= 360;
	else if (retur <= 0)
		retur += 360;
	return (retur);
}

t_position	ft_incr_pos(t_env *env, int sign)
{
	env->pos.speed = 0.1;
	env->pos.x += sign * env->pos.speed * cos(env->pos.dir * DTOR);
	env->pos.y -= sign * env->pos.speed * sin(env->pos.dir * DTOR);
	if (env->pos.x < 1.25 || env->pos.x > env->size_x - 1.25)
		env->pos.x -= sign * env->pos.speed * cos(env->pos.dir * DTOR);
	if (env->pos.y < 1.25 || env->pos.y > env->size_y - 1.25)
		env->pos.y += sign * env->pos.speed * sin(env->pos.dir * DTOR);
	return (env->pos);
}

void	ft_reset_opti(char **opti)
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
