/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 06:04:56 by mmassarw          #+#    #+#             */
/*   Updated: 2023/05/28 11:44:12 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	check_hit(t_vert to_check, char **map)
{
	size_t	len;

	len = 0;
	while (map[len])
		len++;
	if (to_check.y >= 0 && (size_t) to_check.y < len)
		if (to_check.x >= 0 && (size_t) to_check.x < ft_strlen(map[to_check.y]))
			if (map[to_check.y][to_check.x] == '1')
				return (true);
	return (false);
}

void	render_ray(t_ray ray, t_env *data, int idx)
{
	int y_start = ((HEIGHT / 2) - ray.proj_height/2); 
	int y_end = ((HEIGHT / 2) + ray.proj_height/2); 
	int	i = 0;

	while(y_start + i <= y_end)
	{
			pixel_put(data, (t_vert) {WIDTH - idx, y_start + i}, ft_mlx_get_color(data->tex[ray.texture], ray.texture_x * data->tex[ray.texture].width / MAP_SCALE, i * data->tex[ray.texture].height / ray.proj_height));
			i++;
	}
}

void	fill_area(t_env *data, t_vert top_left, t_vert bottom_right, int color)
{
	int x;
	int y;

	y = top_left.y;
	while (y <= bottom_right.y)
	{
		x = top_left.x;
		while (x <= bottom_right.x)
		{
			t_vert pos = {x, y};
			pixel_put(data, pos, color);
			x++;
		}
		y++;
	}
}

void	raycasting(t_env *data)
{
	t_ray		rays[WIDTH];
	int			i[2];
	t_rayutils	rayutils;

	rayutils.angle = data->pos.dir - (data->init.fov / 2) + 1e-6;
	fill_area(data, (t_vert) {0,0}, (t_vert) {WIDTH, HEIGHT/2}, data->init.ceiling);
	fill_area(data, (t_vert) {0,HEIGHT/2}, (t_vert) {WIDTH, HEIGHT}, data->init.floor);
	ft_bzero(i, sizeof(int) * 2);
	i[0] = -1;
	while(++i[0] < WIDTH)
	{
		rayutils.sin_angle = sin(rayutils.angle * DTOR) * -1;
		rayutils.cos_angle = cos(rayutils.angle * DTOR);

		if (rayutils.sin_angle > 0)
		{
			rayutils.edge = ((int) data->pos.y + 1) * MAP_SCALE;
			rayutils.delta_y = MAP_SCALE;
		}
		else
		{
			rayutils.edge = (((int) data->pos.y) - 1e-6) * MAP_SCALE;
			rayutils.delta_y = -MAP_SCALE;
		}
		rayutils.horizental_depth = (rayutils.edge - data->pos.y * MAP_SCALE) / rayutils.sin_angle;
		rayutils.horizental_wall = data->pos.x * MAP_SCALE + rayutils.horizental_depth * rayutils.cos_angle;
		rayutils.delta_depth = rayutils.delta_y / rayutils.sin_angle;
		rayutils.delta_x = rayutils.delta_depth * rayutils.cos_angle;
		i[1] = 0;
		while(i[1]++ < MAX_DEPTH)
		{
			rayutils.check_vert = (t_vert) {(int)  rayutils.horizental_wall / MAP_SCALE, (int) rayutils.edge / MAP_SCALE};
			if (check_hit(rayutils.check_vert, data->map))
				break;
			rayutils.horizental_wall += rayutils.delta_x;
			rayutils.edge += rayutils.delta_y;
			rayutils.horizental_depth += rayutils.delta_depth;
		}

		if (rayutils.cos_angle > 0)
		{
			rayutils.edge = ((int) data->pos.x + 1) * MAP_SCALE;
			rayutils.delta_x = MAP_SCALE;
		}
		else
		{
			rayutils.edge = (((int) data->pos.x) - 1e-6) * MAP_SCALE;
			rayutils.delta_x = -MAP_SCALE;
		}
		rayutils.vertical_depth = (rayutils.edge - data->pos.x * MAP_SCALE) / rayutils.cos_angle;
		rayutils.vertical_wall = data->pos.y * MAP_SCALE + rayutils.vertical_depth * rayutils.sin_angle;
		rayutils.delta_depth = rayutils.delta_x / rayutils.cos_angle;
		rayutils.delta_y = rayutils.delta_depth * rayutils.sin_angle;
		i[1] = 0;
		while(i[1]++ < MAX_DEPTH)
		{
			rayutils.check_vert = (t_vert) {(int)  rayutils.edge / MAP_SCALE, (int) rayutils.vertical_wall / MAP_SCALE};
			if (check_hit(rayutils.check_vert, data->map))
				break;
			rayutils.vertical_wall += rayutils.delta_y;
			rayutils.edge += rayutils.delta_x;
			rayutils.vertical_depth += rayutils.delta_depth;
		}

		if (rayutils.vertical_depth < rayutils.horizental_depth)
		{
			rays[i[0]].depth = rayutils.vertical_depth;
			if (rayutils.cos_angle < 0)
			{
				rays[i[0]].texture = EA;
				rays[i[0]].texture_x = MAP_SCALE - ((int) rayutils.vertical_wall % MAP_SCALE);
			}
			else
			{
				rays[i[0]].texture = WE;
				rays[i[0]].texture_x = (int) rayutils.vertical_wall % MAP_SCALE;
			}
		}
		else
		{
			rays[i[0]].depth = rayutils.horizental_depth;
			if (rayutils.sin_angle > 0)
			{
				rays[i[0]].texture = NO;
				rays[i[0]].texture_x = MAP_SCALE - ((int) rayutils.horizental_wall % MAP_SCALE);
			}
			else
			{
				rays[i[0]].texture = SO;
				rays[i[0]].texture_x = (int) rayutils.horizental_wall % MAP_SCALE;
			}
		}
		rays[i[0]].depth *= cos((data->pos.dir - rayutils.angle) * DTOR);
		rays[i[0]].proj_height = ((double) (WIDTH / 2) / (tan((double) data->init.fov * DTOR / 2))) / ((rays[i[0]].depth + 1e-6)/MAP_SCALE);

		render_ray(rays[i[0]], data, i[0]);
		rayutils.angle += ((double) data->init.fov / (double) WIDTH);
	}
}