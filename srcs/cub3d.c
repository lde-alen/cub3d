/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 17:03:21 by lde-alen          #+#    #+#             */
/*   Updated: 2023/05/28 17:31:29 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	america(t_env *env)
{
	int	i;

	i = -1;
	env->init.texture[0] = ft_free(env->init.texture[0]);
	env->init.texture[1] = ft_free(env->init.texture[1]);
	env->init.texture[2] = ft_free(env->init.texture[2]);
	env->init.texture[3] = ft_free(env->init.texture[3]);
	env->size_line = ft_free(env->size_line);
	while (env->map[++i])
		env->map[i] = ft_free(env->map[i]);
	env->map[i] = ft_free(env->map[i]);
	env->map = ft_free(env->map);
	i = -1;
	while (env->mlx.img.opti[++i])
		env->mlx.img.opti[i] = ft_free(env->mlx.img.opti[i]);
	env->mlx.img.opti = ft_free(env->mlx.img.opti);
}

int	init(char *file)
{
	t_env		env;
	char		*error;
	int			fd;

	env.init = init_map_struct();
	env.pos = init_position();
	env.key = init_key();
	fd = open(file, O_RDONLY);
	if (fd == -1 || read(fd, (void *)0, 0) == -1)
		return (ft_error("Error\nCan't open the map !"));
	error = parse(&env.init, &fd);
	if (error)
		return (ft_error(error));
	if (env.init.ceiling == -1 || env.init.floor == -1)
		return (ft_error("Error\nA argument is missing"));
	env.map = init_map(fd, file, &env.size_y);
	env.size_x = find_x(&env);
	if (env.size_x == -1)
		return (ft_error("Error\nMalloc"));
	error = ft_control_map(&env);
	return (init2(&env, error));
}

int	find_x(t_env *env)
{
	int		size;
	int		i;

	i = 0;
	size = 0;
	env->size_line = malloc(sizeof(int) * env->size_y);
	if (!env->size_line)
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

int	init2(t_env *env, char *error)
{
	if (error && error[0] == 'E')
		return (ft_error(error));
	error = init_mlx(env);
	if (error && error[0] == 'E')
		return (ft_error(error));
	america(env);
	return (0);
}

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		printf("Error\nInvalid arguments");
		return (-1);
	}
	if (ft_strcmp(&av[1][(int)(ft_strlen(av[1]) - 4)], ".cub") != 0)
	{
		printf("Error\nFirst arguments is not a .cub");
		return (-1);
	}
	if (init(av[1]) == -1)
		return (-1);
	return (0);
}
