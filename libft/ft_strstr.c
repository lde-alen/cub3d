/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 17:09:33 by lde-alen          #+#    #+#             */
/*   Updated: 2023/05/28 17:09:34 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int		i;
	int		j;
	int		k;
	char	*str;

	i = 0;
	str = (char *)haystack;
	if (needle[i] == '\0')
		return (str);
	while (str[i])
	{
		k = i;
		j = 0;
		while (haystack[k] == needle[j])
		{
			if (needle[j + 1] == '\0')
				return (&str[i]);
			k++;
			j++;
		}
		i++;
	}
	return (0);
}
