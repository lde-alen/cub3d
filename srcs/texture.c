/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 17:04:13 by lde-alen          #+#    #+#             */
/*   Updated: 2023/05/28 17:32:00 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*texture(t_env *s)
{
	int		i;
	int		fd;

	i = -1;
	while (++i < 4)
	{
		fd = open(s->init.texture[i], O_RDONLY);
		if (fd == -1)
			return ("Error\nNot a good texture.");
		s->tex[i].img = mlx_xpm_file_to_image(s->mlx.mlx,
				s->init.texture[i], &s->tex[i].width, &s->tex[i].height);
		if (s->tex[i].img == NULL)
			return ("Error\nNot a good texture.");
		s->tex[i].data.addr = mlx_get_data_addr(s->tex[i].img,
				&s->tex[i].data.bpp, &s->tex[i].data.line_len,
				&s->tex[i].data.end);
		s->tex[i].color = ft_mlx_get_color(s->tex[i], 0, 0);
		close(fd);
	}
	return (NULL);
}

int	ft_mlx_get_color(t_texture text, int x, int y)
{
	unsigned int	color;
	int				index;

	if (x < 0)
		x = 0;
	if (x >= text.width)
		x = text.width - 1;
	if (y < 0)
		y = 0;
	if (y >= text.height)
		y = text.height - 1;
	index = y * text.data.line_len + x * (text.data.bpp / 8);
	color = ((int *)text.data.addr)[index / 4];
	return (color);
}

void	pixel_put(t_env *data, t_vert pos, int color)
{
	char	*pixel;

	if (pos.y < 0 || pos.y >= HEIGHT || pos.x < 0 || pos.x >= WIDTH)
		return ;
	pixel = data->mlx.img.addr + (pos.y * data->mlx.img.line_len
			+ pos.x * (data->mlx.img.bpp / 8));
	*(unsigned int *) pixel = color;
}
