/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 17:03:54 by lde-alen          #+#    #+#             */
/*   Updated: 2023/05/28 17:29:37 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*init_mlx(t_env *s)
{
	char	*error;

	s->mlx.mlx = mlx_init();
	error = texture(s);
	if (error != NULL)
		return (error);
	init_img(s);
	raycasting(s);
	s->mlx.win = mlx_new_window(s->mlx.mlx, WIDTH, HEIGHT, "Cub3D");
	mlx_put_image_to_window(s->mlx.mlx, s->mlx.win, s->mlx.img.img, 0, 0);
	mlx_hook(s->mlx.win, 2, 1L << 0, key_press, (void *)s);
	mlx_hook(s->mlx.win, 3, 1L << 1, key_release, (void *)s);
	mlx_hook(s->mlx.win, 17, 0, red_cross, (void *)0);
	mlx_loop(s->mlx.mlx);
	quit_mlx(s);
	return (NULL);
}

void	init_img(t_env *s)
{
	int		i;
	int		j;

	j = -1;
	s->mlx.img.img = mlx_new_image(s->mlx.mlx,
			WIDTH, HEIGHT);
	if (s->mlx.img.img == NULL)
		quit_mlx(s);
	s->mlx.img.addr = mlx_get_data_addr(s->mlx.img.img,
			&s->mlx.img.bpp, &s->mlx.img.line_len, &s->mlx.img.end);
	s->mlx.img.opti = malloc((HEIGHT + 1) * sizeof(char *));
	if (!s->mlx.img.opti)
		quit_mlx(s);
	while (++j < HEIGHT)
	{
		i = -1;
		s->mlx.img.opti[j] = malloc((WIDTH + 1) * sizeof(char));
		if (!s->mlx.img.opti[j])
			quit_mlx(s);
		while (++i < WIDTH)
			s->mlx.img.opti[j][i] = '0';
		s->mlx.img.opti[j][i] = '\0';
	}
	s->mlx.img.opti[j] = NULL;
}

void	quit_mlx(t_env *s)
{
	int		i;

	i = -1;
	while (++i < 4)
		mlx_destroy_image(s->mlx.mlx, s->tex[i].img);
	mlx_destroy_image(s->mlx.mlx, s->mlx.img.img);
	mlx_destroy_window(s->mlx.mlx, s->mlx.win);
	s->mlx.mlx = ft_free(s->mlx.mlx);
	america(s);
	exit(0);
}

void	nextframe(t_env *data)
{
	mlx_destroy_image(data->mlx.mlx, data->mlx.img.img);
	mlx_clear_window(data->mlx.mlx, data->mlx.win);
	data->mlx.img.img = mlx_new_image(data->mlx.mlx, WIDTH, HEIGHT);
	data->mlx.img.addr = mlx_get_data_addr(data->mlx.img.img,
			&data->mlx.img.bpp, &data->mlx.img.line_len, &data->mlx.img.end);
	raycasting(data);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win,
		data->mlx.img.img, 0, 0);
}
