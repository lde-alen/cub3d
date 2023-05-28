/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 21:06:51 by myvh              #+#    #+#             */
/*   Updated: 2023/05/28 15:26:24 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

static char	*end_line(char *str, int *ptr_flag, int *ptr_i)
{
	char	*rest;
	int		str_size;

	*ptr_i = 0;
	str_size = ft_strlen(str);
	while (str && str[*ptr_i] && *ptr_i < BUFFER_SIZE)
	{
		if (str[*ptr_i] == '\n')
		{
			*ptr_flag = 1;
			rest = ft_substr(str, *ptr_i + 1, str_size - *ptr_i);
			if (!rest)
				return (NULL);
			return (rest);
		}
		*ptr_i = *ptr_i + 1;
	}
	return (NULL);
}

static char	*read_line(const int fd, char **line, int *ptr_rd, int *ptr_flag)
{
	char	*ret;
	char	*buf;
	int		i;

	i = 0;
	ret = NULL;
	buf = ft_strnew(BUFFER_SIZE);
	*ptr_rd = BUFFER_SIZE;
	while (*ptr_rd == BUFFER_SIZE && *ptr_flag == 0)
	{
		ft_bzero(buf, BUFFER_SIZE);
		*ptr_rd = read(fd, buf, BUFFER_SIZE);
		ret = end_line(buf, ptr_flag, &i);
		if (ret == NULL && *ptr_flag == 1)
			return (NULL);
		if (ptr_flag == 0)
			i = ft_strlen(buf);
		*line = ft_strjoin_size(*line, buf, i);
		if (!*line)
			return (NULL);
	}
	free(buf);
	buf = NULL;
	return (ret);
}

static char	*ft_ret(char *ret, int *ptr_flag, int fd, char **line)
{
	char	*tmp;
	int		rd;

	tmp = ret;
	rd = 0;
	ret = end_line(ret, ptr_flag, &rd);
	if (ret == NULL && *ptr_flag == 1)
		return (NULL);
	if (*ptr_flag == 0)
	{
		*line = ft_substr(tmp, 0, ft_strlen(tmp));
		if (!*line)
			return (NULL);
		ret = read_line(fd, line, &rd, ptr_flag);
		if (ret == NULL && *ptr_flag == 1)
			return (NULL);
	}
	else
	{
		*line = ft_substr(tmp, 0, ft_strlen(tmp) - ft_strlen(ret) - 1);
		if (!*line)
			return (NULL);
	}
	free(tmp);
	return (ret);
}

static int	size_line(char **line, const int fd, int *ptr_flag)
{
	static char	*ret;
	int			rd;

	*line = "";
	rd = 0;
	if (ret == NULL)
	{
		*line = ft_strnew(1);
		if (!*line)
			return (-1);
		ret = read_line(fd, line, &rd, ptr_flag);
		if (!ret)
			return (-1);
	}
	else
	{
		ret = ft_ret(ret, ptr_flag, fd, line);
		if (ret == NULL && *ptr_flag == 1)
			return (-1);
	}
	return (rd);
}

int	get_next_line(const int fd, char **line)
{
	int	rd;
	int	end_line_flag;

	end_line_flag = 0;
	if (fd < 0 || BUFFER_SIZE <= 0 || !line || read(fd, line, 0) < 0)
		return (-1);
	*line = NULL;
	rd = size_line(line, fd, &end_line_flag);
	if (end_line_flag == 0)
		return (0);
	if (rd == -1)
		return (-1);
	return (1);
}
