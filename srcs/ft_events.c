/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_events.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myvh <myvh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 20:40:06 by myvh              #+#    #+#             */
/*   Updated: 2023/05/11 05:34:02 by myvh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			red_cross(int key, void *param)
{
	t_env	*env;

	env = (t_env *)param;
	(void)env;
	exit(0);
	return (key);
}

int			key_press(int key, void *param)
{
	t_env *env;

	env = (t_env *)param;
	mlx_clear_window(env->mlx.mlx, env->mlx.win);
	if (key == 119 || key == 65362)
		env->key.w = 1;
	if (key == 115 || key == 65364)
		env->key.s = 1;
	if (key == 97)
		env->key.a = 1;
	if (key == 100)
		env->key.d = 1;
	if (key == 65361)
		env->key.l = 1;
	if (key == 65363)
		env->key.r = 1;
	if (key == 65307)
		ft_quit_mlx(env);
	ft_move(env);
	return (key);
}

int			key_release(int key, void *param)
{
	t_env *env;

	env = (t_env *)param;
	mlx_clear_window(env->mlx.mlx, env->mlx.win);
	if (key == 119 || key == 65362)
		env->key.w = 0;
	if (key == 115 || key == 65364)
		env->key.s = 0;
	if (key == 97)
		env->key.a = 0;
	if (key == 100)
		env->key.d = 0;
	if (key == 65361)
		env->key.l = 0;
	if (key == 65363)
		env->key.r = 0;
	if (key == 65307)
		ft_quit_mlx(env);
	ft_move(env);
	return (key);
}

int			resize_request(void *env)
{
	t_env	*s;
	float	*dist;

	s = (t_env *)env;
	ft_reset_opti(s->mlx.img.opti);
	if (!(dist = ft_printf_wall(env)))
		ft_quit_mlx(env);
	ft_surface_color(s);
	free(dist);
	mlx_put_image_to_window(s->mlx.mlx, s->mlx.win, s->mlx.img.img, 0, 0);
	return (0);
}
