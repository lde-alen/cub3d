/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 20:48:33 by myvh              #+#    #+#             */
/*   Updated: 2023/05/28 15:13:14 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_char_sep(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

static int	ft_strslen(char *str, char *charset)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (str[i])
	{
		if (!ft_char_sep(str[i], charset))
		{
			x++;
			while (!ft_char_sep(str[i], charset) && str[i])
				i++;
		}
		else
			i++;
	}
	return (x);
}

static int	ft_strlen_word(int i, char *str, char *charset)
{
	int	len_word;

	len_word = 0;
	while (str[i] && !(ft_char_sep(str[i], charset)))
	{
		len_word++;
		i++;
	}
	return (len_word);
}

static char	*ft_remp(int size_word, char *str, char *strs, int i)
{
	int	j;

	j = 0;
	while (j < size_word)
	{
		strs[j] = str[i];
		i++;
		j++;
	}
	strs[j] = '\0';
	return (strs);
}

char	**ft_split_str(char *str, char *charset)
{
	int		nb_word;
	char	**strs;
	int		i;
	int		size_word;
	int		l;

	i = 0;
	nb_word = ft_strslen(str, charset);
	l = -1;
	strs = (char **)malloc((nb_word + 1) * sizeof(char *));
	if (!strs)
		return (NULL);
	while (++l < nb_word)
	{
		while (ft_char_sep(str[i], charset))
			i++;
		size_word = ft_strlen_word(i, str, charset);
		strs[l] = (char *)malloc(size_word * sizeof(char) + 1);
		if (!strs[l])
			return (NULL);
		strs[l] = ft_remp(size_word, str, strs[l], i);
		i += size_word;
	}
	strs[l] = NULL;
	return (strs);
}
