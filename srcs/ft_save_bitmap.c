/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_save_bitmap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myvh <myvh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 20:40:51 by myvh              #+#    #+#             */
/*   Updated: 2023/05/09 20:58:35 by myvh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		ft_save_bitmap(t_env *env)
{
	int		fd;
	int		i;

	i = -1;
	fd = open("./image.bmp", O_CREAT | O_WRONLY, S_IRWXU);
	if (fd != -1)
		ft_fill_bmp(env, fd);
	else
		printf("Error\nCreate image doesn't work");
	while (++i < 5)
		mlx_destroy_image(env->mlx.mlx, env->tex[i].img);
	mlx_destroy_image(env->mlx.mlx, env->mlx.img.img);
	mlx_destroy_display(env->mlx.mlx);
	free(env->mlx.mlx);
	ft_free(env);
	exit(0);
}

int			ft_create_image(t_env *env, int fd)
{
	int				i;
	int				j;
	int				color;
	unsigned char	bmppad[3];

	bmppad[0] = 0;
	bmppad[1] = 0;
	bmppad[2] = 0;
	j = -1;
	while (++j < env->init.y_res)
	{
		i = -1;
		while (++i < env->init.x_res)
		{
			color = ((int *)env->mlx.img.addr)[i + (env->init.y_res
				- 1 - j) * env->init.x_res];
			write(fd, &color, 4);
		}
		i = -1;
		while (++i < (4 - (env->init.x_res * 3) % 4) % 4)
			write(fd, &bmppad, 1);
	}
	return (1);
}

void		ft_fill_4_octets(unsigned char *set, int param)
{
	set[0] = (unsigned char)(param);
	set[1] = (unsigned char)(param >> 8);
	set[2] = (unsigned char)(param >> 16);
	set[3] = (unsigned char)(param >> 24);
}

void		ft_fill_bmp(t_env *env, int fd)
{
	unsigned char	bmp_header[14];
	unsigned char	info[40];
	int				i;

	i = -1;
	while (++i < 40)
		info[i] = 0;
	i = -1;
	while (++i < 14)
		bmp_header[i] = 0;
	info[0] = 40;
	ft_fill_4_octets(&info[4], env->init.x_res);
	ft_fill_4_octets(&info[8], env->init.y_res);
	info[12] = 1;
	info[14] = env->mlx.img.bpp;
	bmp_header[0] = 'B';
	bmp_header[1] = 'M';
	ft_fill_4_octets(&bmp_header[2], 54 + 4
		* env->init.x_res * env->init.y_res);
	bmp_header[10] = 54;
	write(fd, bmp_header, 14);
	write(fd, info, 40);
	ft_create_image(env, fd);
	close(fd);
}
