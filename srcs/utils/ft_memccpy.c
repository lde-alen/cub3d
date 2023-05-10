/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myvh <myvh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 20:35:49 by myvh              #+#    #+#             */
/*   Updated: 2023/05/09 20:36:12 by myvh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	int		i;
	char	*dest;
	char	*sorc;

	i = 0;
	dest = (char *)dst;
	sorc = (char *)src;
	while (i < (int)n)
	{
		dest[i] = sorc[i];
		if ((unsigned char)dest[i] == (unsigned char)c)
			return (&dest[i + 1]);
		i++;
	}
	if (n > ft_strlen(dest))
		dest[i] = '\0';
	return (NULL);
}
