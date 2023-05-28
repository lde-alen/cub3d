/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_events.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 16:47:56 by lde-alen          #+#    #+#             */
/*   Updated: 2023/05/28 05:09:29 by lde-alen         ###   ########.fr       */
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
	if (key == KEY_W || key == ARROW_UP)
		env->key.w = 1;
	if (key == KEY_S || key == ARROW_DOWN)
		env->key.s = 1;
	if (key == KEY_A || key == ARROW_LEFT)
		env->key.a = 1;
	if (key == KEY_D || key == ARROW_RIGHT)
		env->key.d = 1;
	if (key == KEY_L)
		env->key.l = 1;
	if (key == KEY_R)
		env->key.r = 1;
	if (key == KEY_ESC)
		ft_quit_mlx(env);
	ft_move(env);
	return (key);
}

int			key_release(int key, void *param)
{
	t_env *env;

	env = (t_env *)param;
	mlx_clear_window(env->mlx.mlx, env->mlx.win);
	if (key == KEY_W || key == ARROW_UP)
		env->key.w = 0;
	if (key == KEY_S || key == ARROW_DOWN)
		env->key.s = 0;
	if (key == KEY_A || key == ARROW_LEFT)
		env->key.a = 0;
	if (key == KEY_D || key == ARROW_RIGHT)
		env->key.d = 0;
	if (key == KEY_L)
		env->key.l = 0;
	if (key == KEY_R)
		env->key.r = 0;
	if (key == KEY_ESC)
		ft_quit_mlx(env);
	ft_move(env);
	return (key);
}