/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addzikow <addzikow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 12:46:40 by addzikow          #+#    #+#             */
/*   Updated: 2021/03/23 16:24:22 by addzikow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_count_base(unsigned long nbr, const char *base)
{
	size_t	i;
	size_t	len_base;

	len_base = ft_strlen(base);
	i = 0;
	while (nbr)
	{
		nbr = nbr / len_base;
		i++;
	}
	return (i);
}
