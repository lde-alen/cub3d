/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprite_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myvh <myvh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 20:41:42 by myvh              #+#    #+#             */
/*   Updated: 2023/05/09 20:58:35 by myvh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_printf_sprite(t_env *env, float *dist)
{
	int		i;
	int		x_text;

	ft_fill_sprite_struct(env);
	i = -1;
	while (++i < env->sprite.nb)
	{
		ft_adjust_sprite_value(env, i);
		if (field_of_view(env, env->sprite.sp[i].ang))
		{
			while (++env->sprite.x < env->sprite.x_end &&
				env->sprite.x < env->init.x_res - 3)
			{
				if (env->sprite.sp[i].d < pow(dist[env->sprite.x] + 0.5, 2))
				{
					x_text = (int)(256 * (env->sprite.x - (-env->sprite.width
					/ 2 + env->sprite.screen_x)) * env->tex[4].width
					/ env->sprite.width) / 256;
					env->sprite.y = env->sprite.y_start;
					while (env->sprite.y < env->sprite.y_end)
						ft_print_sprite(env, x_text);
				}
			}
		}
	}
}

void	ft_print_sprite(t_env *env, int x_text)
{
	int	color;
	int	d;
	int	y_text;

	d = (env->sprite.y) * 256 - env->init.y_res
		* 128 + env->sprite.height * 128;
	y_text = ((d * env->tex[4].height) / env->sprite.height) / 256;
	color = ft_mlx_get_color(env->tex[4], x_text, y_text);
	if (color != env->tex[4].color)
		ft_mlx_pixel_put_sprite(env->mlx.img, env->sprite.x,
			env->sprite.y, color);
	env->sprite.y++;
}

void	ft_fill_sprite_struct(t_env *env)
{
	int		i;

	i = -1;
	while (++i < env->sprite.nb)
	{
		env->sprite.sprite_x = env->sprite.sp[i].x - env->pos.x;
		env->sprite.sprite_y = env->sprite.sp[i].y - env->pos.y;
		env->sprite.sp[i].d = (env->sprite.sprite_x) * (env->sprite.sprite_x)
		+ (env->sprite.sprite_y) * (env->sprite.sprite_y);
		env->sprite.sp[i].ang = ft_find_alpha_sprite(env);
	}
	ft_sort_sprite(env);
}

float	ft_find_alpha_sprite(t_env *env)
{
	float	arctan;
	float	sprite_x;
	float	sprite_y;

	sprite_x = env->sprite.sprite_x;
	sprite_y = env->sprite.sprite_y;
	arctan = atan(ft_abs(env->sprite.sprite_x / env->sprite.sprite_y));
	if (sprite_x < 0 && sprite_y < 0)
		return (arctan + (PI / 2));
	if (sprite_x >= 0 && sprite_y < 0)
		return ((PI / 2) - arctan);
	if (sprite_x < 0 && sprite_y >= 0)
		return ((3 * PI / 2) - arctan);
	else
		return ((3 * PI / 2) + arctan);
}

void	ft_adjust_sprite_value(t_env *env, int i)
{
	float pourcent;

	env->sprite.sprite_x = env->sprite.sp[i].x - env->pos.x;
	env->sprite.sprite_y = env->sprite.sp[i].y - env->pos.y;
	pourcent = (angle(env->sprite.sp[i].ang, env->pos.dir) +
		(PI / 4)) / (PI / 2);
	env->sprite.screen_x = (int)((1 - pourcent) * env->init.x_res);
	env->sprite.height = (int)((float)env->init.y_res * 0.5) /
	(cos(angle(env->sprite.sp[i].ang, env->pos.dir)) *
		sqrt(env->sprite.sp[i].d));
	env->sprite.y_start = -env->sprite.height / 2 + env->init.y_res / 2;
	env->sprite.y_end = env->sprite.height / 2 + env->init.y_res / 2;
	env->sprite.width = (int)(env->tex[4].width * env->sprite.height
		/ env->tex[4].height);
	env->sprite.x = -env->sprite.width / 2 + env->sprite.screen_x - 1;
	env->sprite.x_end = env->sprite.width / 2 + env->sprite.screen_x;
	env->sprite.y_start = env->sprite.y_start < 0 ? 0 : env->sprite.y_start;
	if (env->sprite.y_end >= env->init.y_res)
		env->sprite.y_end = env->init.y_res - 1;
	env->sprite.x = env->sprite.x < 0 ? 0 : env->sprite.x;
	if (env->sprite.x_end >= env->init.x_res)
		env->sprite.x_end = env->init.x_res - 1;
}
