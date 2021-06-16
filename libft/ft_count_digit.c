/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_digit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addzikow <addzikow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 14:36:15 by addzikow          #+#    #+#             */
/*   Updated: 2021/03/24 14:37:25 by addzikow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_digit(int n)
{
	int		numb;
	long	nb;

	nb = n;
	numb = 0;
	if (nb < 0)
		nb = -nb;
	if (nb == 0)
		numb = 1;
	while (nb > 0)
	{
		nb = nb / 10;
		numb++;
	}
	return (numb);
}
