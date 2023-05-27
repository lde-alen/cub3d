/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42za>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 16:35:06 by lde-alen          #+#    #+#             */
/*   Updated: 2023/05/28 02:56:18 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_init_mlx(t_env *s)
{
	char	*error;
	float	*dist;

	s->mlx.mlx = mlx_init();
	error = ft_texture(s);
	if (error != NULL)
		return (error);
	ft_init_img(s);
	dist = ft_printf_wall(s);
	ft_surface_color(s);
	free(dist);
	s->mlx.win = mlx_new_window(s->mlx.mlx, s->init.x_res, s->init.y_res, "Cub3D");
	mlx_put_image_to_window(s->mlx.mlx, s->mlx.win, s->mlx.img.img, 0, 0);
	mlx_hook(s->mlx.win, 2, 1L << 0, key_press, (void *)s);
	mlx_hook(s->mlx.win, 3, 1L << 1, key_release, (void *)s);
	mlx_hook(s->mlx.win, 33, 1L << 0, red_cross, (void *)0);
	mlx_loop(s->mlx.mlx);
	ft_quit_mlx(s);
	return (NULL);
}

void	ft_init_img(t_env *s)
{
	int		i;
	int		j;

	j = -1;
	s->mlx.img.img = mlx_new_image(s->mlx.mlx,
		s->init.x_res, s->init.y_res);
	if (s->mlx.img.img == NULL)
		ft_quit_mlx(s);
	s->mlx.img.addr = mlx_get_data_addr(s->mlx.img.img,
		&s->mlx.img.bpp, &s->mlx.img.line_len, &s->mlx.img.end);
	if (!(s->mlx.img.opti = malloc((s->init.y_res + 1) * sizeof(char *))))
		ft_quit_mlx(s);
	while (++j < s->init.y_res)
	{
		i = -1;
		if (!(s->mlx.img.opti[j] = malloc((s->init.x_res + 1) * sizeof(char))))
			ft_quit_mlx(s);
		while (++i < s->init.x_res)
			s->mlx.img.opti[j][i] = '0';
		s->mlx.img.opti[j][i] = '\0';
	}
	s->mlx.img.opti[j] = NULL;
}

void	ft_surface_color(t_env *s)
{
	int		x;
	int		y;

	y = 0;
	while (y < s->init.y_res)
	{
		x = 0;
		while (x < s->init.x_res)
		{
			if (y < s->init.y_res * s->pos.z / 4)
				ft_mlx_pixel_put(s->mlx.img, x, y, s->init.ceiling);
			else
				ft_mlx_pixel_put(s->mlx.img, x, y, s->init.floor);
			x++;
		}
		y++;
	}
}

void	ft_quit_mlx(t_env *s)
{
	int		i;

	i = -1;
	while (++i < 4)
		mlx_destroy_image(s->mlx.mlx, s->tex[i].img);
	mlx_destroy_image(s->mlx.mlx, s->mlx.img.img);
	mlx_destroy_window(s->mlx.mlx, s->mlx.win);
	free(s->mlx.mlx);
	ft_america(s);
	exit(0);
}
