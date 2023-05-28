/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 17:03:07 by lde-alen          #+#    #+#             */
/*   Updated: 2023/05/28 17:03:09 by lde-alen         ###   ########.fr       */
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
