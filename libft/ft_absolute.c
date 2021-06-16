/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_absolute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addzikow <addzikow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 10:57:34 by addzikow          #+#    #+#             */
/*   Updated: 2021/05/06 10:49:55 by addzikow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_absolute(int nbr)
{
	long int	nb;

	nb = nbr;
	if (nb < 0)
		nb = nb * -1;
	return ((size_t)nb);
}
