/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 17:06:56 by lde-alen          #+#    #+#             */
/*   Updated: 2023/05/28 17:06:58 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	char	*a;
	int		i;

	i = 0;
	a = (char *)malloc(size);
	if (!a)
		return (NULL);
	while (i < (int)size)
	{
		a[i] = 0;
		i++;
	}
	return ((void *)a);
}
