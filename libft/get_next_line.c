/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myvh <myvh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 21:06:51 by myvh              #+#    #+#             */
/*   Updated: 2023/05/09 21:06:54 by myvh             ###   ########.fr       */
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
			if (!(rest = ft_substr(str, *ptr_i + 1, str_size - *ptr_i)))
				return (NULL);
			return (rest);
		}
		*ptr_i = *ptr_i + 1;
	}
	return (NULL);
}

static char	*read_line(const int fd, char **line, int *ptr_rd, int *ptr_flag)
{
	char	*reste;
	char	*buf;
	int		i;

	i = 0;
	reste = NULL;
	if (!(buf = ft_strnew(BUFFER_SIZE)))
		return (NULL);
	*ptr_rd = BUFFER_SIZE;
	while (*ptr_rd == BUFFER_SIZE && *ptr_flag == 0)
	{
		ft_bzero(buf, BUFFER_SIZE);
		*ptr_rd = read(fd, buf, BUFFER_SIZE);
		reste = end_line(buf, ptr_flag, &i);
		if (reste == NULL && *ptr_flag == 1)
			return (NULL);
		if (ptr_flag == 0)
			i = ft_strlen(buf);
		if (!(*line = ft_strjoin_size(*line, buf, i)))
			return (NULL);
	}
	free(buf);
	buf = NULL;
	return (reste);
}

static char	*ft_reste(char *reste, int *ptr_flag, int fd, char **line)
{
	char	*tmp;
	int		rd;

	tmp = reste;
	rd = 0;
	reste = end_line(reste, ptr_flag, &rd);
	if (reste == NULL && *ptr_flag == 1)
		return (NULL);
	if (*ptr_flag == 0)
	{
		if (!(*line = ft_substr(tmp, 0, ft_strlen(tmp))))
			return (NULL);
		reste = read_line(fd, line, &rd, ptr_flag);
		if (reste == NULL && *ptr_flag == 1)
			return (NULL);
	}
	else
	{
		if (!(*line = ft_substr(tmp, 0, ft_strlen(tmp) - ft_strlen(reste) - 1)))
			return (NULL);
	}
	free(tmp);
	return (reste);
}

static int	size_line(char **line, const int fd, int *ptr_flag)
{
	static char	*reste;
	int			rd;

	*line = "";
	rd = 0;
	if (reste == NULL)
	{
		if (!(*line = ft_strnew(1)))
			return (-1);
		if (!(reste = read_line(fd, line, &rd, ptr_flag)))
			return (-1);
	}
	else
	{
		reste = ft_reste(reste, ptr_flag, fd, line);
		if (reste == NULL && *ptr_flag == 1)
			return (-1);
	}
	return (rd);
}

int			get_next_line(const int fd, char **line)
{
	int rd;
	int end_line_flag;

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
