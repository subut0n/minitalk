/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addzikow <addzikow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 12:39:57 by addzikow          #+#    #+#             */
/*   Updated: 2021/05/20 14:17:24 by addzikow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long int	ft_atol(const char *str)
{
	long int	final;
	int	sign;
	int	i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	sign = 1;
	if ((str[i] == '+') || (str[i] == '-'))
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	final = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		final = final * 10 + sign * (str[i] - 48);
		i++;
	}
	return (final);
}