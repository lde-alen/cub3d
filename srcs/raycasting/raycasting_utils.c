/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmassarw <mmassarw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 06:04:56 by mmassarw          #+#    #+#             */
/*   Updated: 2023/05/28 14:48:10 by mmassarw         ###   ########.fr       */
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
	int	y_start;
	int	y_end;
	int	i;

	y_start = ((HEIGHT / 2) - ray.proj_height / 2);
	y_end = ((HEIGHT / 2) + ray.proj_height / 2);
	if (ray.proj_height > HEIGHT)
	{
		i = ((ray.proj_height - HEIGHT) / 2) - 10;
		y_end -= ((ray.proj_height - HEIGHT) / 2) + 10;
	}
	else
		i = 0;
	while (y_start + i <= y_end)
	{
		pixel_put(data, (t_vert){WIDTH - idx, y_start + i}, \
ft_mlx_get_color(data->tex[ray.texture], ray.texture_x * \
data->tex[ray.texture].width / MAP_SCALE, \
i * data->tex[ray.texture].height / ray.proj_height));
			i++;
	}
}

void	fill_area(t_env *data, t_vert top_left, t_vert bottom_right, int color)
{
	int		x;
	int		y;
	t_vert	pos;

	y = top_left.y;
	while (y <= bottom_right.y)
	{
		x = top_left.x;
		while (x <= bottom_right.x)
		{
			pos = (t_vert){x, y};
			pixel_put(data, pos, color);
			x++;
		}
		y++;
	}
}
