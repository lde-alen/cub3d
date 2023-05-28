/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 17:07:55 by lde-alen          #+#    #+#             */
/*   Updated: 2023/05/28 17:07:56 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *s1, const char *s2)
{
	int	size_s1;
	int	i;

	i = 0;
	size_s1 = ft_strlen(s1);
	while (s2[i])
	{
		s1[i + size_s1] = s2[i];
		i++;
	}
	s1[i + size_s1] = '\0';
	return (s1);
}
