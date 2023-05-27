/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42za>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 20:39:58 by myvh              #+#    #+#             */
/*   Updated: 2023/05/28 02:56:12 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_america(t_env *env)
{
	int	i;

	i = -1;
	free(env->init.texture[0]);
	free(env->init.texture[1]);
	free(env->init.texture[2]);
	free(env->init.texture[3]);
	free(env->size_line);
	while (env->map[++i])
		free(env->map[i]);
	free(env->map[i]);
	free(env->map);
	i = -1;
	while (env->mlx.img.opti[++i])
		free(env->mlx.img.opti[i]);
	free(env->mlx.img.opti);
}

int		ft_init_struct(char *file)
{
	t_env		env;
	char		*error;
	int			fd;

	env.init = ft_init_map_struct();
	env.pos = ft_init_position();
	env.key = ft_init_key();
	fd = open(file, O_RDONLY);
	if (fd == -1 || read(fd, (void *)0, 0) == -1)
		return (ft_error("Error\nCan't open the map !"));
	if (!(!(error = ft_parse(&env.init, &fd))))
		return (ft_error(error));
	if (env.init.ceiling == -1 || env.init.floor == -1 || env.init.x_res == -1)
		return (ft_error("Error\nA argument is missing"));
	env.map = ft_init_map(fd, file, &env.size_y);
	env.size_x = ft_find_size_x(&env);
	if (env.size_x == -1)
		return (ft_error("Error\nMalloc"));
	error = ft_control_map(&env);
	return (ft_init_struct2(&env,  error));
}

int		ft_find_size_x(t_env *env)
{
	int		size;
	int		i;

	i = 0;
	size = 0;
	if (!(env->size_line = malloc(sizeof(int) * env->size_y)))
		return (-1);
	while (env->map[i])
	{
		env->size_line[i] = ft_strlen(env->map[i]);
		if (env->size_line[i] > size)
			size = env->size_line[i];
		i++;
	}
	return (size);
}

int		ft_init_struct2(t_env *env,  char *error)
{
	if (error && error[0] == 'E')
		return (ft_error(error));
	error = ft_init_mlx(env);
	if (error && error[0] == 'E')
		return (ft_error(error));
	ft_america(env);
	return (0);
}

int		main(int ac, char **av)
{
	if (ac != 2)
	{
		printf("Error: Invalid arguments");
		return (-1);
	}
	if (ft_strcmp(&av[1][(int)(ft_strlen(av[1]) - 4)], ".cub") != 0)
	{
		printf("Error\nFirst arguments is not a .cub");
		return (-1);
	}
	if (ft_init_struct(av[1]) == -1)
		return (-1);
	return (0);
}
