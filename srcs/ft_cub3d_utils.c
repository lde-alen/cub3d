/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 17:10:33 by lde-alen          #+#    #+#             */
/*   Updated: 2023/05/28 17:10:34 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_error(char *error)
{
	write(2, error, ft_strlen(error));
	return (-1);
}

int	ft_check_color(int r, int g, int b)
{
	if (r < 0 || r > 255)
		return (-1);
	if (g < 0 || g > 255)
		return (-1);
	if (b < 0 || b > 255)
		return (-1);
	return (0);
}
