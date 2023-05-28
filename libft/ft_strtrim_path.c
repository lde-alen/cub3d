/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 20:47:04 by myvh              #+#    #+#             */
/*   Updated: 2023/05/28 15:08:02 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	space(const char *c, int j, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c[j] == set[i] && c[j - 1] != '\\')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim_path(char const *s1, char const *set)
{
	int		i;
	int		size;
	int		j;
	char	*str;

	i = 0;
	j = 1;
	size = ft_strlen(s1);
	while (space(s1, i, set) && s1[i])
		i++;
	while (space(s1, size - j, set) && s1[size - j])
		j++;
	if (i == size)
		return (ft_strnew(0));
	str = ft_substr(s1, i, size - i - j + 1);
	if (!str)
		return (NULL);
	i = -1;
	while (str[++i])
		if (str[i] == ' ' && str[i - 1] == '\\')
			ft_strcpy(&str[i - 1], &str[i]);
	return (str);
}
