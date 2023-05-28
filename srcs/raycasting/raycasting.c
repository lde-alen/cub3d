/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 06:04:56 by mmassarw          #+#    #+#             */
/*   Updated: 2023/05/28 17:31:18 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	cast_hor(t_env *data, t_rutl *rutl)
{
	int	i;

	i = 0;
	if (rutl->sin_a > 0)
		rutl->xtra = (t_utlpls){((int) data->pos.y + 1) * MAP_SCALE, MAP_SCALE};
	else
		rutl->xtra = (t_utlpls){(((int) data->pos.y) - 1e-6) * MAP_SCALE, \
	-MAP_SCALE};
	rutl->hor_depth = (rutl->xtra.edge - data->pos.y * MAP_SCALE) / rutl->sin_a;
	rutl->hor_wl = data->pos.x * MAP_SCALE + rutl->hor_depth * rutl->cos_a;
	rutl->ddepth = rutl->xtra.dmain / rutl->sin_a;
	rutl->dothr = rutl->ddepth * rutl->cos_a;
	while (i++ < MAX_DEPTH)
	{
		rutl->chk = (t_vert){(int) rutl->hor_wl / MAP_SCALE, \
	(int) rutl->xtra.edge / MAP_SCALE};
		if (check_hit(rutl->chk, data->map))
			break ;
		rutl->hor_wl += rutl->dothr;
		rutl->xtra.edge += rutl->xtra.dmain;
		rutl->hor_depth += rutl->ddepth;
	}
}

static void	cast_vert(t_env *data, t_rutl *rutl)
{
	int	i;

	i = 0;
	if (rutl->cos_a > 0)
		rutl->xtra = (t_utlpls){((int) data->pos.x + 1) * MAP_SCALE, MAP_SCALE};
	else
		rutl->xtra = (t_utlpls){(((int) data->pos.x) - 1e-6) * MAP_SCALE, \
	-MAP_SCALE};
	rutl->ver_depth = (rutl->xtra.edge - data->pos.x * MAP_SCALE) / rutl->cos_a;
	rutl->ver_wl = data->pos.y * MAP_SCALE + rutl->ver_depth * rutl->sin_a;
	rutl->ddepth = rutl->xtra.dmain / rutl->cos_a;
	rutl->dothr = rutl->ddepth * rutl->sin_a;
	while (i++ < MAX_DEPTH)
	{
		rutl->chk = (t_vert){(int) rutl->xtra.edge / MAP_SCALE, \
	(int) rutl->ver_wl / MAP_SCALE};
		if (check_hit(rutl->chk, data->map))
			break ;
		rutl->ver_wl += rutl->dothr;
		rutl->xtra.edge += rutl->xtra.dmain;
		rutl->ver_depth += rutl->ddepth;
	}
}

static t_ray	init_ray(t_rutl rutl)
{
	t_ray	ray;

	if (rutl.ver_depth < rutl.hor_depth)
	{
		ray.depth = rutl.ver_depth;
		if (rutl.cos_a < 0)
		{
			ray.texture = EA;
			ray.texture_x = MAP_SCALE - ((int) rutl.ver_wl % MAP_SCALE);
			return (ray);
		}
		ray.texture = WE;
		ray.texture_x = (int) rutl.ver_wl % MAP_SCALE;
		return (ray);
	}
	ray.depth = rutl.hor_depth;
	ray.texture = SO;
	ray.texture_x = (int) rutl.hor_wl % MAP_SCALE;
	if (rutl.sin_a > 0)
	{
		ray.texture = NO;
		ray.texture_x = MAP_SCALE - ((int) rutl.hor_wl % MAP_SCALE);
	}
	return (ray);
}

void	raycasting(t_env *data)
{
	t_ray		rays[WIDTH];
	int			i;
	t_rutl		rutl;

	rutl.a = data->pos.dir - (data->init.fov / 2) + 1e-6;
	fill_area(data, (t_vert){0, 0}, \
	(t_vert){WIDTH, HEIGHT / 2}, data->init.ceiling);
	fill_area(data, (t_vert){0, HEIGHT / 2}, \
	(t_vert){WIDTH, HEIGHT}, data->init.floor);
	i = -1;
	while (++i < WIDTH)
	{
		rutl.sin_a = sin(rutl.a * DTOR) * -1;
		rutl.cos_a = cos(rutl.a * DTOR);
		cast_hor(data, &rutl);
		cast_vert(data, &rutl);
		rays[i] = init_ray(rutl);
		rays[i].depth *= cos((data->pos.dir - rutl.a) * DTOR);
		rays[i].proj_height = ((double)(WIDTH / 2) / (tan((double) \
	data->init.fov * DTOR / 2))) / ((rays[i].depth + 1e-6) / MAP_SCALE);
		render_ray(rays[i], data, i);
		rutl.a += ((double) data->init.fov / (double) WIDTH);
	}
}
