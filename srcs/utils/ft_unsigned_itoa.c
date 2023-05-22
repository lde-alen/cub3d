/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigned_itoa.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myvh <myvh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 20:35:00 by myvh              #+#    #+#             */
/*   Updated: 2023/05/09 20:45:29 by myvh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_count_char(unsigned int num)
{
	int				i;

	i = 0;
	while (num >= 1)
	{
		num = num / 10;
		i++;
	}
	return (i);
}

char		*ft_unsigned_itoa(unsigned int num)
{
	int				i;
	char			*str;
	int				size;

	i = 1;
	if (num != 0)
		size = ft_count_char(num);
	else
   		size = 1;
	if (!(str = (char *)malloc((size + 1) * sizeof(char))))
		return (NULL);
	if (num != 0)
    	str[0] = '-';
	else
    	str[0] = '0';
	while (num >= 1)
	{
		str[size - i] = num % 10 + '0';
		num = num / 10;
		i++;
	}
	str[size] = '\0';
	return (str);
}