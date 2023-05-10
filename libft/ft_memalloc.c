/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myvh <myvh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 20:46:28 by myvh              #+#    #+#             */
/*   Updated: 2023/05/09 21:03:49 by myvh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	char	*a;
	int		i;

	i = 0;
	if (!(a = (char *)malloc(size)))
		return (NULL);
	while (i < (int)size)
	{
		a[i] = 0;
		i++;
	}
	return ((void *)a);
}
