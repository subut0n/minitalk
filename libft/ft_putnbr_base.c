/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addzikow <addzikow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 14:51:17 by addzikow          #+#    #+#             */
/*   Updated: 2021/03/23 16:37:57 by addzikow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_check_base(const char *base)
{
	int	i;
	int	j;
	int	len;

	len = ft_strlen(base);
	if (len == 1 || len == 0)
		return (0);
	i = 0;
	while (base[i])
	{
		if (base[i] == '-' || base[i] == '+')
			return (0);
		j = i + 1;
		while (base[j])
		{
			if (base[i] == base[j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	ft_printnbr_base(unsigned long long nb, const char *base)
{
	unsigned long int	size_of_base;
	int					checkbase;

	size_of_base = ft_strlen(base);
	checkbase = ft_check_base(base);
	if (checkbase == 0)
		ft_putchar('\0');
	else
	{
		if (nb <= size_of_base - 1)
		{
			ft_putchar(base[nb]);
		}
		else
		{
			ft_printnbr_base(nb / size_of_base, base);
			ft_printnbr_base(nb % size_of_base, base);
		}
	}
}

void	ft_putnbr_base(unsigned long nbr, const char *base)
{
	ft_printnbr_base((unsigned long)nbr, base);
}
