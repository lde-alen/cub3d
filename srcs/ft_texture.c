/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_texture.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myvh <myvh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 20:41:55 by myvh              #+#    #+#             */
/*   Updated: 2023/05/09 20:58:35 by myvh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_texture(t_env *s)
{
	int		i;
	int		fd;

	i = -1;
	while (++i < 5)
	{
		fd = open(s->init.texture[i], O_RDONLY);
		if (fd == -1)
			return ("Error\nNot a good texture.");
		s->tex[i].img = mlx_xpm_file_to_image(s->mlx.mlx,
			s->init.texture[i], &s->tex[i].width, &s->tex[i].height);
		if (s->tex[i].img == NULL)
			return ("Error\nNot a good texture.");
		s->tex[i].data.addr = mlx_get_data_addr(s->tex[i].img,
			&s->tex[i].data.bpp, &s->tex[i].data.line_len, &s->tex[i].data.end);
		s->tex[i].color = ft_mlx_get_color(s->tex[i], 0, 0);
		close(fd);
	}
	return (NULL);
}

int		ft_mlx_get_color(t_texture text, int x, int y)
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

void	ft_mlx_pixel_put(t_img image, int x, int y, int color)
{
	char	*dst;

	if (image.opti[y][x] == '0')
	{
		dst = image.addr + (y * image.line_len + x * (image.bpp / 8));
		*(unsigned int*)dst = color;
		image.opti[y][x] = '1';
	}
}

void	ft_mlx_pixel_put_sprite(t_img image, int x, int y, int color)
{
	char	*dst;

	dst = image.addr + (y * image.line_len + x * (image.bpp / 8));
	*(unsigned int*)dst = color;
}
